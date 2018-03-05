(use-syntax (ice-9 syncase))

(define-syntax my-let
        (syntax-rules ()
        ((let ((name val) ...) body1 body2 ...)
                ((lambda (name ...) body1 body2 ...)
                        val ...))))


(define-syntax my-let*
        (syntax-rules ()
        ((my-let* () body1 body2 ...)
                (my-let () body1 body2 ...))
                ((my-let* ((name1 val1) (name2 val2) ...)
                        body1 body2 ...)
                (my-let ((name1 val1))
                        (my-let* ((name2 val2) ...)
                                body1 body2 ...)))))
