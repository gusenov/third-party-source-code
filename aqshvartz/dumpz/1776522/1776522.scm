(define-syntax when 
  (syntax-rules ()
    ((_ cond-expr . exprs) 
     (if cond-expr (begin . exprs)))))

(define x 1)
;(when   (> x 0) (display "x > 0")  (newline))

(define-syntax unless
  (syntax-rules ()
    ((_ cond-expr . exprs)
     (if (not cond-expr) (begin . exprs)))))

;(unless (= x 0) (display "x != 0") (newline))

(define-syntax for
  (syntax-rules (as in) 
    ((_ items as item . body) (for-each (lambda (item) .  body) items))
    ((_ item in items . body) (for items  as item . body))))

#|
(for i in '(1 2 3)
  (for j in '(4 5 6)
    (display (list i j))
    (newline)))
|#

(define-syntax while
  (syntax-rules ()
    ((_ cond-expr . exprs)
     (letrec ((iter (lambda ()
                     (if cond-expr
                         (begin
                         (begin . exprs)
                         (iter))
                         )))) (iter)))))

(define-syntax repeat
  (syntax-rules ()
    ((_  (exp . exprs) until cond-expr)
     (letrec ((iter (lambda()
                      (begin
                      (begin exp . exprs)
                      (if (not cond-expr)
                          (iter))))))
       (iter)))))
                      
                        
(define-syntax cout
  (syntax-rules ()
    ((_ '(<< arg2 . alist)  ys) (if (equal? 'arg2 'endl) (cout 'alist (cons '(newline) ys)) (cout 'alist (cons '(display arg2) ys))))
    ((_ '() xs) (eval (cons 'begin (reverse xs)) (interaction-environment)))
    ((_ . xs) (cout 'xs '()))
    ))
                              
;(cout << "a = " << 1 << endl << "b = " << 2 << endl)    
              