(use-syntax (ice-9 syncase))

(define-syntax define-data
  (syntax-rules ()
    ((_ type constructors) (define-type `type `constructors))))

(define (define-type type constructors)
  (define (define-constructor constructor)
    (eval
     `(define ,constructor (list ',(car constructor) ,@(cdr constructor)))
     (interaction-environment)))
  (define (define-predicate)
    (eval
     `(define (,(string->symbol (string-append (symbol->string type) "?")) p)
        (and
         (list? p) (> (length p) 0)
         (assoc (car p) ',constructors) #t))
     (interaction-environment)))
  
  (define-predicate)
  (for-each define-constructor constructors))

(define-syntax match
  (syntax-rules ()
    ((_ f) #f)
    ((_ f ((shape-type args ...) expr) exprs ...) (or
                                                   (and
                                                    (list? f) (> (length f) 0)
                                                    (equal? (car f) 'shape-type)
                                                    (equal? (length (cdr f)) (length '(args ...)))
                                                    (eval
                                                     (cons '(lambda (args ...) expr) (cdr f))
                                                     (interaction-environment)))
                                                   (match f exprs ...)))))