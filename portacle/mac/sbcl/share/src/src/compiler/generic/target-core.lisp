;;;; target-only code that knows how to load compiled code directly
;;;; into core
;;;;
;;;; FIXME: The filename here is confusing because "core" here means
;;;; "main memory", while elsewhere in the system it connotes a
;;;; ".core" file dumping the contents of main memory.

;;;; This software is part of the SBCL system. See the README file for
;;;; more information.
;;;;
;;;; This software is derived from the CMU CL system, which was
;;;; written at Carnegie Mellon University and released into the
;;;; public domain. The software is in the public domain and is
;;;; provided with absolutely no warranty. See the COPYING and CREDITS
;;;; files for more information.

(in-package "SB-C")

;;; Map of code-component -> list of PC offsets at which allocations occur.
;;; This table is needed in order to enable allocation profiling.
(define-load-time-global *allocation-patch-points*
  (make-hash-table :test 'eq :weakness :key :synchronized t))

#-x86-64
(progn
(defun sb-vm::statically-link-code-obj (code fixups)
  (declare (ignore code fixups))))

#+immobile-code
(progn
  ;; Use FDEFINITION because it strips encapsulations - whether that's
  ;; the right behavior for it or not is a separate concern.
  ;; If somebody tries (TRACE LENGTH) for example, it should not cause
  ;; compilations to fail on account of LENGTH becoming a closure.
  (defun sb-vm::function-raw-address (name &aux (fun (fdefinition name)))
    (cond ((not (immobile-space-obj-p fun))
           (error "Can't statically link to ~S: code is movable" name))
          ((neq (%fun-pointer-widetag fun) sb-vm:simple-fun-widetag)
           (error "Can't statically link to ~S: non-simple function" name))
          (t
           (let ((addr (get-lisp-obj-address fun)))
             (sap-ref-word (int-sap addr)
                           (- (ash sb-vm:simple-fun-self-slot sb-vm:word-shift)
                              sb-vm:fun-pointer-lowtag))))))

  ;; Return the address to which to jump when calling FDEFN,
  ;; which is either an fdefn or the name of an fdefn.
  ;; FIXME: Shouldn't this go in x86-64-vm ?
  (defun sb-vm::fdefn-entry-address (fdefn)
    (let ((fdefn (if (fdefn-p fdefn) fdefn (find-or-create-fdefn fdefn))))
      (+ (get-lisp-obj-address fdefn)
         (- 2 sb-vm:other-pointer-lowtag)))))

;;; Point FUN's 'self' slot to FUN.
;;; FUN must be pinned when calling this.
#-darwin-jit ; done entirely by C for #+darwin-jit
(defmacro assign-simple-fun-self (fun)
  `(let* ((fun ,fun)
          (self
           ;; a few architectures store the untagged address of the entrypoint in 'self'
           #+(or x86 x86-64 arm64)
           (%make-lisp-obj
            (truly-the word (+ (get-lisp-obj-address fun)
                               (ash sb-vm:simple-fun-insts-offset sb-vm:word-shift)
                               (- sb-vm:fun-pointer-lowtag))))
           ;; all others store the function itself (what else?) in 'self'
           #-(or x86 x86-64 arm64) fun))
     (setf (sb-vm::%simple-fun-self fun) self)))

(define-load-time-global sb-fasl::*asm-routine-index-to-name* #())
(declaim (simple-vector sb-fasl::*asm-routine-index-to-name*))

(flet ((fixup (code-obj offset name kind flavor preserved-lists statically-link-p)
         (declare (ignorable statically-link-p))
         ;; NAME depends on the kind and flavor of fixup.
         ;; PRESERVED-LISTS is a vector of lists of locations (by kind)
         ;; at which fixup must be re-applied after code movement.
         ;; CODE-OBJ must already be pinned in order to legally call this.
         ;; One call site that reaches here is below at MAKE-CORE-COMPONENT
         ;; and the other is LOAD-CODE, both of which pin the code.
         (ecase
             (sb-vm:fixup-code-object
                 code-obj offset
                 (ecase flavor
                   ((:assembly-routine :assembly-routine* :asm-routine-nil-offset)
                    (- (or (get-asm-routine name (eq flavor :assembly-routine*))
                           (error "undefined assembler routine: ~S" name))
                       (if (eq flavor :asm-routine-nil-offset) sb-vm:nil-value 0)))
                   (:foreign (foreign-symbol-address name))
                   (:foreign-dataref (foreign-symbol-address name t))
                   (:code-object (get-lisp-obj-address code-obj))
                   #+sb-thread (:symbol-tls-index (ensure-symbol-tls-index name))
                   (:layout (get-lisp-obj-address
                             (wrapper-friend (if (symbolp name) (find-layout name) name))))
                   (:layout-id (layout-id name))
                   #+gencgc (:gc-barrier (extern-alien "gc_card_table_nbits" int))
                   (:immobile-symbol (get-lisp-obj-address name))
                   ;; It is legal to take the address of symbol-value only if the
                   ;; value is known to be an immobile object
                   ;; (whose address we don't want to wire in).
                   (:symbol-value (get-lisp-obj-address (symbol-global-value name)))
                   #+immobile-code
                   (:named-call
                    (prog1 (sb-vm::fdefn-entry-address name) ; creates if didn't exist
                      (when statically-link-p
                        (push (cons offset (find-fdefn name)) (elt preserved-lists 0)))))
                   #+immobile-code (:static-call (sb-vm::function-raw-address name)))
                 kind flavor)
           ((nil)) ; don't need to save it in the code-fixups, otherwise do
           (:relative (push offset (elt preserved-lists 1)))
           (:absolute (push offset (elt preserved-lists 2)))
           (:immediate (push offset (elt preserved-lists 3)))
           (:absolute64 (push offset (elt preserved-lists 4)))))

       (finish-fixups (code-obj preserved-lists)
         (declare (ignorable code-obj preserved-lists))
         ;; PRESERVED-LISTS are somewhat backend-dependent, but essentially
         ;; you get to store three lists that might as well have been named
         ;; Larry, Moe, and Curly.
         (let ((rel-fixups (elt preserved-lists 1))
               (abs-fixups (elt preserved-lists 2))
               (gc-barrier-fixups (elt preserved-lists 3))
               (abs64-fixups (elt preserved-lists 4)))
           ;; the fixup list packer only preserves at most 3 lists.
           ;; And it's not clear that this is the best way to represent them.
           (aver (not abs64-fixups))
           (when (or abs-fixups rel-fixups gc-barrier-fixups)
             (setf (sb-vm::%code-fixups code-obj)
                   (sb-c:pack-code-fixup-locs abs-fixups rel-fixups gc-barrier-fixups))))

         ;; Assign all SIMPLE-FUN-SELF slots unless #+darwin-jit in which case the simple-funs
         ;; are assigned by jit_memcpy_codeblob()
         #-darwin-jit
         (dotimes (i (code-n-entries code-obj))
           (let ((fun (%code-entry-point code-obj i)))
             (assign-simple-fun-self fun)
             ;; And maybe store the layout in the high half of the header
             #+(and compact-instance-header x86-64)
             (setf (sap-ref-32 (int-sap (get-lisp-obj-address fun))
                               (- 4 sb-vm:fun-pointer-lowtag))
                   (truly-the (unsigned-byte 32)
                     (get-lisp-obj-address (wrapper-friend #.(find-layout 'function)))))))
         ;; And finally, make the memory range executable.
         ;; x86 doesn't need it, and darwin-jit doesn't do it because the
         ;; temporary object is not executable.
         #-(or x86 x86-64 darwin-jit) (sb-vm:sanctify-for-execution code-obj)
         ;; Return fixups amenable to static linking
         (aref preserved-lists 0)))

  (defun apply-fasl-fixups (code-obj fixups index count &aux (end (1- (+ index count))))
    (dx-let ((preserved (make-array 5 :initial-element nil)))
      (awhen (svref fixups index)
        (setf (gethash code-obj *allocation-patch-points*) it))
      (loop
        (when (>= index end) (return))
        (binding* (((offset kind flavor data)
                    (sb-fasl::!unpack-fixup-info (svref fixups (incf index))))
                   (name
                    (cond ((member flavor '(:code-object :gc-barrier)) nil)
                          ((and (plusp data)
                                (member flavor '(:assembly-routine :assembly-routine*)))
                           (aref sb-fasl::*asm-routine-index-to-name* data))
                          (t (svref fixups (incf index))))))
          (fixup code-obj offset name kind flavor preserved nil)))
      (finish-fixups code-obj preserved)))

  (defun apply-core-fixups (code-obj fixup-notes)
    (declare (list fixup-notes))
    (dx-let ((preserved (make-array 5 :initial-element nil)))
      (dolist (note fixup-notes)
        (let ((fixup (fixup-note-fixup note))
              (offset (fixup-note-position note)))
          (fixup code-obj offset
                 (fixup-name fixup)
                 (fixup-note-kind note)
                 (fixup-flavor fixup)
                 preserved t)))
      (finish-fixups code-obj preserved))))

;;; Return a behaviorally identical copy of CODE which is used for TRACE
;;; in "funobj encapsulation" mode where we just switch an entry point
;;; so that it jumps to a tracing routine and then back again.
;;; The code that gets copied is just the tracing wrapper.
;;; See the example at COMPILE-FUNOBJ-ENCAPSULATION in ntrace
#+(or x86 x86-64)
(defun copy-code-object (code)
  ;; Must have one simple-fun
  (aver (= (code-n-entries code) 1))
  ;; Disallow relative instruction operands.
  ;; (This restriction could be removed by actually performing fixups)
  ;; x86-64 absolute fixups are OK since they will only point to static objects.
  #+x86-64
  (aver (not (nth-value
              1 (sb-c:unpack-code-fixup-locs (sb-vm::%code-fixups code)))))
  (aver (zerop (code-n-named-calls code)))
  (let* ((nbytes (code-object-size code))
         (boxed (code-header-words code)) ; word count
         (unboxed (- nbytes (ash boxed sb-vm:word-shift))) ; byte count
         (copy (allocate-code-object :dynamic boxed unboxed)))
    (with-pinned-objects (code copy)
      (%byte-blt (code-instructions code) 0 (code-instructions copy) 0 unboxed)
      ;; copy boxed constants so that the fixup step (if needed) sees the 'fixups'
      ;; slot from the new object.
      (loop for i from 2 below boxed
            do (setf (code-header-ref copy i) (code-header-ref code i)))
      ;; x86 needs to fixup instructions that reference code constants,
      ;; and the jmp to TAIL-CALL-VARIABLE
      #+x86 (alien-funcall (extern-alien "gencgc_apply_code_fixups" (function void unsigned unsigned))
                           (- (get-lisp-obj-address code) sb-vm:other-pointer-lowtag)
                           (- (get-lisp-obj-address copy) sb-vm:other-pointer-lowtag))
      (assign-simple-fun-self (%code-entry-point copy 0)))
    copy))

;;; Dump a component to core. We pass in the assembler fixups, code
;;; vector and node info.

;;; Note that it is critical that the new code object not be movable after
;;; copying in unboxed bytes and prior to fixing up those bytes.
;;; Why: suppose the object has a jump table initially filled with addends of
;;; 0x1000, 0x1100, 0x1200 representing the label offsets. If GC moves the object,
;;; it adds the amount of movement to those labels. If it moves by, say +0x5000,
;;; then the addends get mangled into 0x6000, 0x6100, 0x6200.
;;; When we then add those addends to the virtual address of the code to
;;; perform fixup application, the resulting addresses are all wrong.
;
;;; While GC might be made to use a heuristic to decide whether the label offsets
;;; had been fixed up at all, it would be fragile nonetheless, because an offset
;;; could theoretically resemble a valid address on machines where code resides
;;; at low addresses in an object whose size is large. e.g. for an object which
;;; spans the range 0x10000..0x30000 in memory, and the word 0x11000 in the jump
;;; table, does that word represent an already-fixed-up label offset of 0x01000,
;;; or an un-fixed-up value which needs to become 0x21000 ? It's ambiguous.
;;; We could add 1 bit to the code object signifying that fixups had beeen applied
;;; for the first time. But that complication is not needed, as long as we keep the
;;; code pinned. That suffices because prior to copying in anything, all bytes
;;; are 0, so the jump table count is 0.
;;; Similar considerations pertain to x86[-64] fixups within the machine code.

(defun code-header/trailer-adjust (code-obj expected-nwords n-fdefns)
  (declare (ignorable expected-nwords n-fdefns))
  ;; Serial# shares a word with the jump-table word count,
  ;; so we can't assign serial# until after all raw bytes are copied in.
  ;; Do we need unique IDs on the various strange kind of code blobs? These would
  ;; include code from MAKE-SIMPLIFYING-TRAMPOLINE, ENCAPSULATE-FUNOBJ, MAKE-BPT-LRA.
  (let* ((serialno (ldb (byte (byte-size sb-vm::code-serialno-byte) 0)
                        (atomic-incf *code-serialno*)))
         (insts (code-instructions code-obj))
         (jumptable-word (sap-ref-word insts 0)))
    (aver (zerop (ash jumptable-word -14)))
    (setf (sap-ref-word insts 0) ; insert serialno
          (logior (ash serialno (byte-position sb-vm::code-serialno-byte))
                  jumptable-word)))
  #+64-bit
  (let ((base (sap+ (int-sap (get-lisp-obj-address code-obj)) (- sb-vm:other-pointer-lowtag)))
        (physical-nwords ; upper 4 bytes of the header word
         (ash (get-header-data code-obj) -24)))
    (setf (sap-ref-32 base (+ (ash sb-vm:code-boxed-size-slot sb-vm:word-shift)
                              #+little-endian 4))
          n-fdefns)
    (when (/= physical-nwords expected-nwords)
      ;; Oversized allocation must be exactly 2 words more than requested
      (aver (= (- physical-nwords 2) expected-nwords))
      ;; Point just beyond the trailer word (physically and where it should be)
      (let* ((new-trailer (sap+ base (ash physical-nwords sb-vm:word-shift)))
             (old-trailer (sap+ base (ash (- physical-nwords 2) sb-vm:word-shift)))
             (trailer-length (sap-ref-16 old-trailer -2)) ; in bytes
             (trailer-nelements (floor trailer-length 4)))
        ;; this is a memmove() and memset()
        (dotimes (i trailer-nelements)
          ;; Transfer 4 bytes per element (uint32_t), highest address first
          ;; since we're moving upward in memory.
          (let ((offset (* (1+ i) -4)))
            (setf (sap-ref-32 new-trailer offset) (sap-ref-32 old-trailer offset) )))
        ;; Zeroize at most 4 elements in the "old" trailer. These will be the
        ;; items at the lowest addresses (the highest indices in negative order).
        ;; If there are fewer than 4 elements, then only zeroize that many.
        (loop for offset from (* trailer-nelements -4) by 4
              repeat (min trailer-nelements 4)
              do (setf (sap-ref-32 old-trailer offset) 0))
        ;; Increase the trailer length by 2 lispwords
        (incf (sap-ref-16 new-trailer -2) (* 2 sb-vm:n-word-bytes)))))
  ;; Enforce that the final unboxed data word is published to memory
  ;; before the debug-info is set.
  (sb-thread:barrier (:write)))

#+darwin-jit
(defun assign-code-constants (code data)
  (let* ((sb-vm::*pinned-objects* ; Pin DATA plus every element of it.
          (list* code data (nconc (coerce data 'list) sb-vm::*pinned-objects*))))
    (sb-vm::jit-copy-code-constants (get-lisp-obj-address code)
                                    (get-lisp-obj-address data))))

(defun make-core-component (component segment length fixup-notes alloc-points object)
  (declare (type component component)
           (type segment segment)
           (type index length)
           (list fixup-notes)
           (type core-object object))
  (binding*
        ((debug-info (debug-info-for-component component))
         (2comp (component-info component))
         (constants (ir2-component-constants 2comp))
         (n-boxed-words (length constants))
         (boxed-data
          ;; <header, boxed_size, debug_info, fixups> are absent from the simple-vector
          (or #+darwin-jit
              (make-array (- n-boxed-words sb-vm:code-constants-offset) :initial-element 0)))
         (const-patch-start-index
          (+ sb-vm:code-constants-offset (* (length (ir2-component-entries 2comp))
                                            sb-vm:code-slots-per-simple-fun)))
         (n-named-calls
          ;; Pre-scan for fdefinitions to ensure their existence.
          ;; Doing so guarantees that storing them into the boxed header now
          ;; can't create any old->young pointer, which is important since gencgc
          ;; does not deal with untagged pointers when looking for old->young.
          (do ((count 0)
               (index const-patch-start-index (1+ index)))
              ((>= index n-boxed-words) count)
            (let ((const (aref constants index)))
              (when (and (listp const) (case (car const)
                                         (:named-call (incf count))
                                         (:fdefinition t)))
                (setf (second const) (find-or-create-fdefn (second const)))))))
         ((code-obj total-nwords)
          (allocate-code-object (component-mem-space component)
                                (align-up n-boxed-words code-boxed-words-align)
                                length))
         (bytes
          (the (simple-array assembly-unit 1) (segment-contents-as-vector segment)))
         (n-simple-funs (length (ir2-component-entries 2comp)))
         (named-call-fixups nil))
    (declare (ignorable boxed-data))
    (sb-fasl::with-writable-code-instructions
        (code-obj total-nwords debug-info n-named-calls n-simple-funs)
      :copy (%byte-blt bytes 0 (code-instructions code-obj) 0 (length bytes))
      :fixup (setq named-call-fixups (apply-core-fixups code-obj fixup-notes)))

    (when alloc-points
      #+(and x86-64 sb-thread)
      (if (= (extern-alien "alloc_profiling" int) 0) ; record the object for later
          (setf (gethash code-obj *allocation-patch-points*) alloc-points)
          (funcall 'sb-aprof::patch-code code-obj alloc-points)))

    (push debug-info (core-object-debug-info object))

    ;; Don't need code pinned now
    ;; (It will implicitly be pinned on the conservatively scavenged backends)
    (macrolet ((set-boxed-word (i val &optional fdefnp)
                 (declare (ignorable fdefnp))
                 ;; Thankfully we don't mix untagged fdefns with darwin-jit
                 #+darwin-jit
                 `(setf (svref boxed-data (- ,i ,sb-vm:code-constants-offset)) ,val)
                 #-darwin-jit
                 (if (not fdefnp) ; statically not an fdefn
                     `(setf (code-header-ref code-obj ,i) ,val)
                     `(if ,fdefnp ; else choose which setter to use
                          (set-code-fdefn code-obj ,i ,val)
                          (setf (code-header-ref code-obj ,i) ,val)))))

      (let* ((entries (ir2-component-entries 2comp))
             (fun-index (length entries)))
        (dolist (entry-info entries)
          (let ((fun (%code-entry-point code-obj (decf fun-index)))
                (w (+ sb-vm:code-constants-offset
                      (* sb-vm:code-slots-per-simple-fun fun-index))))
            (aver (functionp fun)) ; in case %CODE-ENTRY-POINT returns NIL
            (set-boxed-word (+ w sb-vm:simple-fun-name-slot) (entry-info-name entry-info))
            (set-boxed-word (+ w sb-vm:simple-fun-arglist-slot) (entry-info-arguments entry-info))
            (set-boxed-word (+ w sb-vm:simple-fun-source-slot) (entry-info-form/doc entry-info))
            (set-boxed-word (+ w sb-vm:simple-fun-info-slot) (entry-info-type/xref entry-info))
            (setf (gethash entry-info (core-object-entry-table object)) fun))))

      (do ((index const-patch-start-index (1+ index)))
          ((>= index n-boxed-words))
        (let* ((const (aref constants index))
               (kind (if (listp const) (car const) const)))
          (set-boxed-word
           index
           (etypecase kind
             ((eql :entry)
              (the function (gethash (leaf-info (cadr const))
                                     (core-object-entry-table object))))
             ((member :named-call :fdefinition) (cadr const))
             ((eql :known-fun) (%coerce-name-to-fun (cadr const)))
             (constant (constant-value const)))
           (eq kind :named-call))))

      #+darwin-jit (assign-code-constants code-obj boxed-data))

    (when named-call-fixups
      (sb-vm::statically-link-code-obj code-obj named-call-fixups))
    (when sb-fasl::*show-new-code*
      (let ((*print-pretty* nil))
        (format t "~&New code(~Db,core): ~A~%" (code-object-size code-obj) code-obj)))
    code-obj))

(defun set-code-fdefn (code index fdefn)
  #+untagged-fdefns
  (with-pinned-objects (fdefn)
    (setf (code-header-ref code index)
          (%make-lisp-obj (logandc2 (get-lisp-obj-address fdefn)
                                    sb-vm:lowtag-mask))))
  #-untagged-fdefns
  (setf (code-header-ref code index) fdefn))

;;; Backpatch all the DEBUG-INFOs dumped so far with the specified
;;; SOURCE-INFO list. We also check that there are no outstanding
;;; forward references to functions.
(defun fix-core-source-info (info object &optional function)
  (declare (type core-object object))
  (declare (type (or null function) function))
  (let ((source (debug-source-for-info info :function function)))
    (dolist (info (core-object-debug-info object))
      (setf (debug-info-source info) source)))
  (setf (core-object-debug-info object) nil)
  (values))
