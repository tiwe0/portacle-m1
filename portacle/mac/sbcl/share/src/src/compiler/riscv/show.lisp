;;;; VOPs which are useful for following the progress of the system
;;;; early in boot

;;;; This software is part of the SBCL system. See the README file for
;;;; more information.
;;;;
;;;; This software is derived from the CMU CL system, which was
;;;; written at Carnegie Mellon University and released into the
;;;; public domain. The software is in the public domain and is
;;;; provided with absolutely no warranty. See the COPYING and CREDITS
;;;; files for more information.

(in-package "SB-VM")

(define-vop (print)
  (:args (object :scs (descriptor-reg any-reg) :target ca0))
  (:results (result :scs (descriptor-reg)))
  (:save-p t)
  (:temporary (:sc any-reg :offset ca0-offset :from (:argument 0)) ca0)
  (:temporary (:sc any-reg :offset cfunc-offset) cfunc)
  (:temporary (:sc control-stack :offset nfp-save-offset) nfp-save)
  (:vop-var vop)
  (:generator 100
    (let ((cur-nfp (current-nfp-tn vop)))
      (when cur-nfp
        (store-stack-tn nfp-save cur-nfp))
      (move ca0 object)
      (inst li cfunc (make-fixup "debug_print" :foreign))
      (inst jal ra-tn (make-fixup 'call-into-c :assembly-routine))
      (when cur-nfp
        (load-stack-tn cur-nfp nfp-save))
      (move result ca0))))
