(use-syntax (ice-9 syncase))

(define (make-source sequence . eof)
  (define (helper)
    (or
     (and (string? sequence) (string->list sequence))
     (and (vector? sequence) (vector->list sequence))
     (and (list? sequence) sequence)))
  (or
   (and (null? eof) (list (helper) #f))
   (list (helper) (car eof))))

(define-syntax peek
  (syntax-rules ()
    ((_ s) (if (null? (car s))
               (cadr s)
               (caar s)))))

(define-syntax next
  (syntax-rules ()
    ((_ s) (if (null? (car s))
               (cadr s)
               (let ((answer (caar s)))
                 (begin (set! s (list (cdar s) (cadr s))) 
                        answer))))))