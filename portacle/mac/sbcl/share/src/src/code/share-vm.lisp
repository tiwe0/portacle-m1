;;;; arch-independent runtime stuff
;;;; This software is part of the SBCL system. See the README file for
;;;; more information.
;;;;
;;;; This software is derived from the CMU CL system, which was
;;;; written at Carnegie Mellon University and released into the
;;;; public domain. The software is in the public domain and is
;;;; provided with absolutely no warranty. See the COPYING and CREDITS
;;;; files for more information.

(in-package "SB-VM")

(defvar *current-internal-error-context*)

(defmacro with-pinned-context-code-object
      ((&optional (context '*current-internal-error-context*))
       &body body)
    (declare (ignorable context))
    #+(or x86 x86-64)
    `(progn ,@body)
    #-(or x86 x86-64)
    `(with-pinned-objects ((with-code-pages-pinned (:dynamic)
                             (sb-di::code-object-from-context ,context)))
       ,@body))

;;;; OS-CONTEXT-T

;;; a POSIX signal context, i.e. the type passed as the third
;;; argument to an SA_SIGACTION-style signal handler
;;;
;;; The real type does have slots, but at Lisp level, we never
;;; access them, or care about the size of the object. Instead, we
;;; always refer to these objects by pointers handed to us by the C
;;; runtime library, and ask the runtime library any time we need
;;; information about the contents of one of these objects. Thus, it
;;; works to represent this as an object with no slots.
;;;
;;; KLUDGE: It would be nice to have a type definition analogous to
;;; C's "struct os_context_t;", for an incompletely specified object
;;; which can only be referred to by reference, but I don't know how
;;; to do that in the FFI, so instead we just this bogus no-slots
;;; representation. -- WHN 20000730
;;;
;;; FIXME: Since SBCL, unlike CMU CL, uses this as an opaque type,
;;; it's no longer architecture-dependent, and probably belongs in
;;; some other package, perhaps SB-KERNEL.
(define-alien-type os-context-t (struct os-context-t-struct))

;; KLUDGE: Linux/MIPS signal context fields are 64 bits wide, even on
;; 32-bit systems.  On big-endian implementations, simply using a
;; pointer to a narrower type DOES NOT WORK because it reads the upper
;; half of the value, not the lower half.  On such systems, we must
;; either read the entire value (and mask down, in case the system
;; sign-extends the value, which has been seen to happen), or offset
;; the pointer in order to read the lower half.  This has been broken
;; at least twice in the past.  MIPS also appears to be the ONLY
;; system for which the signal context field size may differ from
;; n-word-bits.
(defconstant kludge-big-endian-short-pointer-offset
  (+ 0
     #+(and mips big-endian (not 64-bit)) 1))

(declaim (inline context-pc))
(defun context-pc (context)
  (declare (type (alien (* os-context-t)) context))
  (alien-funcall (extern-alien "os_context_pc" (function system-area-pointer (* os-context-t)))
                 context))

(declaim (inline set-context-pc))
(defun set-context-pc (context new)
  (declare (type (alien (* os-context-t)) context))
  (with-pinned-context-code-object (context)
    (alien-funcall (extern-alien "set_os_context_pc" (function void (* os-context-t) unsigned))
                   context new)))

(declaim (inline incf-context-pc))
(defun incf-context-pc (context offset)
  (declare (type (alien (* os-context-t)) context))
  (with-pinned-context-code-object (context)
    (set-context-pc context (sap-int (sap+ (context-pc context) offset)))))

(declaim (inline context-register-addr))
(define-alien-routine ("os_context_register_addr" context-register-addr)
    (* unsigned)
  (context (* os-context-t))
    (index int))

(sb-c::when-vop-existsp  (:translate sb-c::unsigned+)
  (declaim (inline os-context-flags-addr))
  (define-alien-routine ("os_context_flags_addr" os-context-flags-addr)
      (* unsigned)
    (context (* os-context-t)))

  (declaim (inline context-flags))
  (defun context-flags (context)
    (declare (type (alien (* os-context-t)) context))
    (let ((addr (os-context-flags-addr context)))
      (declare (type (alien (* unsigned)) addr))
      (deref addr))))

(declaim (inline context-register))
(defun context-register (context index)
  (declare (type (alien (* os-context-t)) context))
  (let ((addr (context-register-addr context index)))
    (declare (type (alien (* unsigned)) addr))
    (deref addr kludge-big-endian-short-pointer-offset)))

(declaim (inline %set-context-register))
(defun %set-context-register (context index new)
  (declare (type (alien (* os-context-t)) context))
  (let ((addr (context-register-addr context index)))
    (declare (type (alien (* unsigned)) addr))
    (setf (deref addr kludge-big-endian-short-pointer-offset) new)))

(declaim (inline boxed-context-register))
(defun boxed-context-register (context index)
  (declare (type (alien (* os-context-t)) context))
  (let ((addr (context-register-addr context index)))
    (declare (type (alien (* unsigned)) addr))
    ;; No LISPOBJ alien type, so grab the SAP and use SAP-REF-LISPOBJ.
    (sap-ref-lispobj
     (alien-sap addr)
     (* kludge-big-endian-short-pointer-offset n-word-bytes))))

(declaim (inline %set-boxed-context-register))
(defun %set-boxed-context-register (context index new)
  (declare (type (alien (* os-context-t)) context))
  (let ((addr (context-register-addr context index)))
    (declare (type (alien (* unsigned)) addr))
    ;; No LISPOBJ alien type, so grab the SAP and use SAP-REF-LISPOBJ.
    (setf (sap-ref-lispobj (alien-sap addr)
                           (* kludge-big-endian-short-pointer-offset
                              n-word-bytes))
          new)))

;;; Convert the descriptor into a SAP. The bits all stay the same, we just
;;; change our notion of what we think they are.
(declaim (inline descriptor-sap))
(defun descriptor-sap (x) (int-sap (get-lisp-obj-address x)))



(eval-when (:compile-toplevel :load-toplevel :execute)
  (defparameter *cpu-features* nil))

(defmacro def-cpu-feature (name detect)
  ;; eval-when doesn't work correctly in the XC
  (setf (getf *cpu-features* name) detect)
  `(progn
     (defglobal ,(symbolicate '+ name '-routines+) ())
     (setf (getf *cpu-features* ',name) ',detect)))

(defmacro def-variant (name cpu-feature lambda-list &body body)
  (let ((variant (symbolicate name '- cpu-feature)))
    `(progn
       (defun ,variant ,lambda-list
         ,@body)
       ;; Avoid STATICALLY-LINK-CORE from making it harder to redefine.
       (proclaim '(notinline ,name))
       (setf (getf ,(symbolicate '+ cpu-feature '-routines+) (find-fdefn ',name))
             #',variant))))

(defvar *previous-cpu-routines* nil)

(defmacro setup-cpu-specific-routines ()
  `(progn
     ,@(loop for (feature detect) on *cpu-features* by #'cddr
             collect
             `(when ,detect
                (loop for (fdefn definition) on ,(package-symbolicate :sb-vm '+ feature '-routines+)
                      by #'cddr
                      do
                      (push (cons fdefn (fdefn-fun fdefn))
                            *previous-cpu-routines*)
                      (setf (fdefn-fun fdefn) definition))))))

(defun restore-cpu-specific-routines ()
  (loop for (fdefn . fun) in *previous-cpu-routines*
        do (setf (fdefn-fun fdefn) fun))
  (setf *previous-cpu-routines* nil))
