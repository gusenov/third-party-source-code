(define define-memoized (lambda (func)
                  (let ((memo '()))
                    (lambda args
                      (let ((match (assoc args memo)))
                        (if match
                            (cadr match)                  
                            (let ((value (apply func args)))
                              (set! memo (cons (list args value) memo))
                              value)))))))
