;;; -*-  Lisp -*-
(error "Can't build contribs with ASDF")

(defsystem "sb-cltl2"
    :description "Functionality mentioned in CLtL2 but not present in ANSI."
    :components ((:file "defpackage")
                 (:file "compiler-let" :depends-on ("defpackage"))
                 (:file "env" :depends-on ("defpackage"))))
