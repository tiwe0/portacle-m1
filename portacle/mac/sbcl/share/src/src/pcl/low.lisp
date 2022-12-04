;;;; This file contains portable versions of low-level functions and macros
;;;; which are ripe for implementation specific customization. None of the code
;;;; in this file *has* to be customized for a particular Common Lisp
;;;; implementation. Moreover, in some implementations it may not make any
;;;; sense to customize some of this code.
;;;;
;;;; The original version was intended to support portable customization to
;;;; lotso different Lisp implementations. This functionality is gone in the
;;;; current version, and it now runs only under SBCL. (Now that ANSI Common
;;;; Lisp has mixed CLOS into the insides of the system (e.g. error handling
;;;; and printing) so deeply that it's not very meaningful to bootstrap Common
;;;; Lisp without CLOS, the old functionality is of dubious use. -- WHN
;;;; 19981108)

;;;; This software is part of the SBCL system. See the README file for more
;;;; information.

;;;; This software is derived from software originally released by Xerox
;;;; Corporation. Copyright and release statements follow. Later modifications
;;;; to the software are in the public domain and are provided with
;;;; absolutely no warranty. See the COPYING and CREDITS files for more
;;;; information.

;;;; copyright information from original PCL sources:
;;;;
;;;; Copyright (c) 1985, 1986, 1987, 1988, 1989, 1990 Xerox Corporation.
;;;; All rights reserved.
;;;;
;;;; Use and copying of this software and preparation of derivative works based
;;;; upon this software are permitted. Any distribution of this software or
;;;; derivative works must comply with all applicable United States export
;;;; control laws.
;;;;
;;;; This software is made available AS IS, and Xerox Corporation makes no
;;;; warranty about the software, its performance or its conformity to any
;;;; specification.

(in-package "SB-PCL")

;;; The PCL package is internal and is used by code in potential
;;; bottlenecks. And since it's internal, no one should be
;;; doing things like deleting and recreating it in a running target Lisp.
(define-symbol-macro *pcl-package* #.(find-package "SB-PCL"))

(declaim (inline defstruct-classoid-p))
(defun defstruct-classoid-p (classoid)
  ;; It is non-obvious to me why STRUCTURE-CLASSOID-P doesn't
  ;; work instead of this. -- NS 2008-03-14
  (typep (sb-kernel::wrapper-%info (classoid-wrapper classoid))
         'defstruct-description))

;;; This excludes structure types created with the :TYPE option to
;;; DEFSTRUCT. It also doesn't try to deal with types created by
;;; hairy DEFTYPEs, e.g.
;;;   (DEFTYPE CACHE-STRUCTURE (SIZE)
;;;     (IF (> SIZE 11) 'BIG-CS 'SMALL-CS)).
;;; KLUDGE: In fact, it doesn't seem to deal with DEFTYPEs at all. Perhaps
;;; it needs a more mnemonic name. -- WHN 19991204
(defun structure-type-p (type)
  (and (symbolp type)
       (let ((classoid (find-classoid type nil)))
         (and classoid
              (not (condition-classoid-p classoid))
              (defstruct-classoid-p classoid)))))

;;; Symbol contruction utilities
(defun format-symbol (package format-string &rest format-arguments)
  (without-package-locks
   (intern (possibly-base-stringize
            (apply #'format nil format-string format-arguments))
           package)))

(defun condition-type-p (type)
  (and (symbolp type)
       (condition-classoid-p (find-classoid type nil))))

(defmacro dotimes-fixnum ((var count &optional (result nil)) &body body)
  `(dotimes (,var (the fixnum ,count) ,result)
     (declare (fixnum ,var))
     ,@body))

(define-load-time-global *pcl-misc-random-state* (make-random-state))

(declaim (inline random-fixnum))
(defun random-fixnum ()
  (random (1+ most-positive-fixnum)
          (load-time-value *pcl-misc-random-state*)))

;;; Lambda which executes its body (or not) randomly. Used to drop
;;; random cache entries.
;;; This formerly punted with slightly greater than 50% probability,
;;; and there was a periodicity to the nonrandomess.
;;; If that was intentional, it should have been commented to that effect.
(defmacro randomly-punting-lambda (lambda-list &body body)
  (with-unique-names (drops drop-pos)
    `(let ((,drops (random-fixnum)) ; means a POSITIVE fixnum
           (,drop-pos sb-vm:n-positive-fixnum-bits))
       (declare (fixnum ,drops)
                (type (mod #.sb-vm:n-fixnum-bits) ,drop-pos))
       (lambda ,lambda-list
         (when (logbitp (the unsigned-byte (decf ,drop-pos)) ,drops)
           (locally ,@body))
         (when (zerop ,drop-pos)
           (setf ,drops (random-fixnum)
                 ,drop-pos sb-vm:n-positive-fixnum-bits))))))

(defun set-funcallable-instance-function (fin new-value)
  (declare (type function new-value))
  ;; It's not worth bothering to teach the compiler to efficiently transform
  ;; a type test involving FUNCALLABLE-STANDARD-OBJECT, not the least
  ;; of the problems being that the type isn't known during make-host-2.
  (unless (and (function-with-layout-p fin)
               (logtest (layout-flags (%fun-layout fin))
                        +pcl-object-layout-flag+))
    (error 'type-error :datum fin :expected-type 'funcallable-standard-object))
  (setf (%funcallable-instance-fun fin) new-value))

;;; FIXME: these macros should just go away.  It's not clear whether
;;; the inline functions defined by
;;; !DEFSTRUCT-WITH-ALTERNATE-METACLASS are as efficient as they could
;;; be; ordinary defstruct accessors are defined as source transforms.
;;; Another thing: if weakening STD-INSTANCE-P to %INSTANCEP is legal within
;;; PCL code, wouldn't it be legal to weaken FSC-INSTANCE-P to FUNCTIONP?
;;; And technically this weaker than the real constraint anyway, as it returns
;;; T on funcallable instances lacking CLOS slots.
(declaim (inline fsc-instance-p))
(defun fsc-instance-p (fin)
  (funcallable-instance-p fin))

(declaim (inline clos-slots-ref (setf clos-slots-ref)))
(declaim (ftype (function (simple-vector t) t) clos-slots-ref))
(defun clos-slots-ref (slots index)
  (svref slots index))
(declaim (ftype (function (t simple-vector t) t) (setf clos-slots-ref)))
(defun (setf clos-slots-ref) (new-value slots index)
  (setf (svref slots index) new-value))

;;; Note on implementation under CMU CL >=17 and SBCL: STD-INSTANCE-P
;;; is only used to discriminate between functions (including FINs)
;;; and normal instances, so we can return true on structures also. A
;;; few uses of (OR STD-INSTANCE-P FSC-INSTANCE-P) are changed to
;;; PCL-INSTANCE-P.
;;; FIXME: this fuction seriously needs to die.  Sometimes "STD-" means things
;;; that are STANDARD-OBJECT including possibly FUNCALLABLE-STANDARD-OBJECT,
;;; but here it means something which is expressly not FUNCALLABLE-STANDARD-OBJECT.
;;; The converse of this is FSC-INSTANCE-P, meaning not STD-INSTANCE-P.
;;; I'm less bothered by that one since "funcallable standard class instance" mostly says
;;; what it means, whereas "standard" is virtually devoid of meaning within this setting.
(declaim (inline std-instance-p))
(defun std-instance-p (x)
  (%instancep x))

;;; When given a funcallable instance, SET-FUN-NAME *must* side-effect
;;; that FIN to give it the name. When given any other kind of
;;; function SET-FUN-NAME is allowed to return a new function which is
;;; "the same" except that it has the name.
;;;
;;; In all cases, SET-FUN-NAME must return the new (or same)
;;; function. (Unlike other functions to set stuff, it does not return
;;; the new value.)
;; This is an absolutely terrible name for a function which both assigns
;; the name slot of a function, and _sometimes_ binds a name to a function.
(defun set-fun-name (fun new-name)
  "Set the name of a compiled function object. Return the function."
  (when (valid-function-name-p fun)
    (setq fun (fdefinition fun)))
  (typecase fun
    (%method-function fun)
    ;; a closure potentially becomes a different closure
    (closure (setq fun (set-closure-name fun t new-name)))
    (t (setf (%fun-name fun) new-name)))
  ;; Fixup name-to-function mappings in cases where the function
  ;; hasn't been defined by DEFUN.  (FIXME: is this right?  This logic
  ;; comes from CMUCL).  -- CSR, 2004-12-31
  ;;
  ;; Now, given this logic is somewhat suspect to begin with, and is the final
  ;; remaining contributor to the immortalization of EQL-specialized methods,
  ;; I'm going to say that we don't create an fdefn for anything
  ;; whose specializers are not symbols.
  ;; Otherwise, adding+removing N methods named
  ;;  (SLOW-METHOD BLAH ((EQL <HAIRY-LIST-OBJECT>)))
  ;; makes them all permanent because FDEFNs are compared by name EQUALity,
  ;; so each gets its own FDEFN. This is bad, and pretty much useless anyway.
  (when (and (consp new-name)
             (or (eq (car new-name) 'slot-accessor)
                 (and (member (car new-name) '(slow-method fast-method))
                      ;; name is: ({SLOW|FAST}-METHOD root <qual>* spec+)
                      (every #'symbolp (car (last new-name))))))
    (setf (fdefinition new-name) fun))
  fun)

;;; This definition is for interpreted code.
;;; FIXME: (1) is EXPLICIT-CHECK really doing anything here?
;;;        (2) why isn't this named STANDARD-OBJECT-P?
(defun pcl-instance-p (x) (declare (explicit-check)) (%pcl-instance-p x))

(defmacro std-instance-slots (x)
  `(truly-the simple-vector (%instance-ref ,x ,sb-vm:instance-data-start)))
(defmacro fsc-instance-slots (x)
  `(truly-the simple-vector (%funcallable-instance-info ,x 0)))

;;; FIXME: These functions are called every place we do a
;;; CALL-NEXT-METHOD, and probably other places too. It's likely worth
;;; selectively optimizing them with DEFTRANSFORMs and stuff, rather
;;; than just indiscriminately expanding them inline everywhere.
(declaim (inline get-slots get-slots-or-nil))
(declaim (ftype (function (t) simple-vector) get-slots))
(declaim (ftype (function (t) (or simple-vector null)) get-slots-or-nil))
(defun get-slots (instance)
  (if (std-instance-p instance)
      (std-instance-slots instance)
      (fsc-instance-slots instance)))
(defun get-slots-or-nil (instance)
  ;; Suppress a code-deletion note.  FIXME: doing the FIXME above,
  ;; integrating PCL more with the compiler, would remove the need for
  ;; this icky stuff.
  (declare (optimize (inhibit-warnings 3)))
  ;; Was: (WHEN (PCL-INSTANCE-P INSTANCE) (GET-SLOTS INSTANCE))
  ;; but we can do better then to perform STD-/FSC- discrimination twice
  ;; (once in the test of PCL-INSTANCE-P and once in GET-SLOTS).
  (cond ((std-instance-p instance) (std-instance-slots instance))
        ((fsc-instance-p instance) (fsc-instance-slots instance))))

(defun pcl-compile (expr &optional unsafe-policy)
  (let* ((base-policy sb-c::*policy*)
         (lexenv
          (sb-c::make-almost-null-lexenv
           (if unsafe-policy
               (sb-c::process-optimize-decl
                '((space 1) (compilation-speed 1)
                  (speed 3) (safety 0) (sb-ext:inhibit-warnings 3) (debug 0))
                base-policy)
               base-policy)
           ;; I suspect that INHIBIT-WARNINGS precludes them from happening
           (list (cons (sb-kernel:find-classoid 'style-warning) 'muffle-warning)
                 (cons (sb-kernel:find-classoid 'compiler-note) 'muffle-warning))
           nil nil nil)))
    (sb-c:compile-in-lexenv expr lexenv nil nil nil nil nil)))

;;; This is here, moved from src/pcl/boot so that it gets a 1-byte layout ID
(defstruct (fast-method-call (:copier nil))
  (function #'identity :type function)
  pv
  next-method-call
  arg-info)
