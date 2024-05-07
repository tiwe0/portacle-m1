(in-package "SB-IMPL")

;;;; generalized function names
(define-load-time-global *valid-fun-names-alist* nil)

(defun %define-fun-name-syntax (symbol checker)
  (let ((found (assoc symbol *valid-fun-names-alist* :test #'eq)))
    (if found
        (setf (cdr found) checker)
        (setq *valid-fun-names-alist*
              (acons symbol checker *valid-fun-names-alist*)))))

(defmacro define-function-name-syntax (symbol (var) &body body)
  "Define function names of the form of a list headed by SYMBOL to be
a legal function name, subject to restrictions imposed by BODY.  BODY
is evaluated with VAR bound to the form required to check, and should
return two values: the first value is a generalized boolean indicating
legality, and the second a symbol for use as a BLOCK name or similar
situations."
  (declare (type symbol symbol))
  (let ((syntax-checker (symbolicate '%check- symbol '-fun-name)))
    `(progn
       (defun ,syntax-checker (,var) ,@body)
       (%define-fun-name-syntax ',symbol #',syntax-checker))))

;;; FIXME: this is a really lame name for something that has two
;;; return values.
;;; See CSR's log comment in bd0ba0f214518e8d72ff2d44de5a1e3e4b02af2c
;;; I would think that after 11 years of we're entitled to rename it.
;;; VALIDATE-FUNCTION-NAME would be apt.
(defun valid-function-name-p (name)
  "The primary return value indicates whether NAME is a valid function
name; if it is, the second return value will be a symbol suitable for
use as a BLOCK name in the function in question."
  (typecase name
    (cons
     (when (symbolp (car name))
       (let ((syntax-checker (cdr (assoc (car name) *valid-fun-names-alist*
                                         :test #'eq))))
         (when syntax-checker
           (funcall syntax-checker name)))))
    (symbol (values t name))
    (otherwise nil)))

(define-function-name-syntax setf (name)
  (let ((tail (cdr name)))
    (when (and (consp tail) (null (cdr tail)))
      (let ((fun (car tail)))
        (typecase fun
          ;; ordinary (SETF FOO) case
          (symbol (values t fun))
          ;; reasonable (SETF (QUUX BAZ)) case [but not (SETF (SETF
          ;; FOO))]
          (cons (unless (member (car fun) '(cas setf))
                  (valid-function-name-p fun))))))))

;;; FBOUNDP wants to know what names are valid early on in COLD-INIT.
(defun !function-names-init ()
  (setq *valid-fun-names-alist* nil)
  ;; CAS and SETF names should have in common the aspect that
  ;; (CAS (CAS BAZ)), (SETF (CAS BAZ)), (CAS (SETF BAZ)) are not reasonable.
  ;; 'cas.lisp' doesn't need to know this technique for sharing the parser,
  ;; so the name syntax is defined here instead of there.
  (%define-fun-name-syntax 'setf #'%check-setf-fun-name)
  (%define-fun-name-syntax 'cas #'%check-setf-fun-name))

#+sb-xc-host
(!function-names-init)
