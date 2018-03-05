(define (factorize xs)
  (cond 
   ((and (equal? (car xs) '-) (equal? (caddr (caddr xs)) 2)) (list '* (list '- (cadr (cadr xs)) (cadr (caddr xs))) (list '+ (cadr (cadr xs))  (cadr (caddr xs)))))
   ((equal? (car xs) '-) (if (equal? (caddr (cadr xs)) 3)  (list '* (list '- (cadr (cadr xs)) (cadr (caddr xs))) (list '+ (list '* (cadr (cadr xs)) (cadr (cadr xs))) (list '* (cadr (cadr xs)) (cadr (caddr xs))) (list '* (cadr (caddr xs)) (cadr (caddr xs)))))))
   ((equal? (car xs) '+) (if (equal? (caddr (cadr xs)) 3)  (list '* (list '+ (cadr (cadr xs)) (cadr (caddr xs))) (list '+ (list '* (cadr (cadr xs)) (cadr (cadr xs))) (list '- (list '* (cadr (cadr xs)) (cadr (caddr xs)))) (list '* (cadr (caddr xs)) (cadr (caddr xs))))))))
  )


;(factorize '(- (expt x 2) (expt y 2)))
;(factorize '(- (expt (+ first 1) 2) (expt (- second 1) 2)))
;(factorize '(- (expt x 3) (expt y 3)))
;(factorize '(+ (expt x 3) (expt y 3)))