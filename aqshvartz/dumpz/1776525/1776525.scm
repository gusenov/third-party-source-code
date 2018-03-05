(define (operator? c)
  (member c '(+ - / *)))

(define (left-paranthesis? c)
  (equal? c '<))

(define (right-paranthesis? c)
  (equal? c '>))

(define (priority a)
  (cond ((member a '(+ -)) 0)
        ((member a '(* /)) 1)
        ((member a '(< >)) -1)))

(define (rpn expr)
  ;
  (define (helper xs stack)
    (or
     (and (null? xs) stack)
     (let ((c (car xs)))
       (or
        (and (left-paranthesis? c) (helper (cdr xs) (cons c stack)))
        (and (right-paranthesis? c) (if (left-paranthesis? (car stack))
                                        (helper (cdr xs) (cdr stack))
                                        (cons (car stack) (helper xs (cdr stack)))))
        (and (operator? c) (if (and (not (null? stack)) (< (priority c) (priority (car stack))))
                               (cons (car stack) (helper xs (cdr stack)))
                               (helper (cdr xs) (cons c stack))))
        (cons c (helper (cdr xs) stack))))))
  (helper expr '()))