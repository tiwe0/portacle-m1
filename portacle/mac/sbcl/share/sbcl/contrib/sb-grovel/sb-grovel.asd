;;; -*-  Lisp -*-

(error "Can't build contribs with ASDF")

(defsystem "sb-grovel"
  :version "0.2"
  :depends-on ("asdf")
  :components ((:file "defpackage")
               (:file "def-to-lisp" :depends-on ("defpackage"))
               (:file "foreign-glue" :depends-on ("defpackage"))))
