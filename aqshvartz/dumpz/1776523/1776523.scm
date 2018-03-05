(define memoized-factorial 
  (let ((memo '()))
    (lambda (n)
      (let ((memoized (assq n memo)))
        (if memoized
            (cadr memoized)
            (let ((new-value  (if (< n 2)  1 (* (memoized-factorial (- n 1)) n))))
              (set! memo
                    (cons (list n new-value) memo))
              new-value))))))


(define-syntax lazy-cons
  (syntax-rules ()
  ((_ a b) (cons a (delay b)))))

(define (naturals start)
  (lazy-cons start (naturals (+ start 1))))


(define lazy-car car)

(define (lazy-cdr ls) (force (cdr ls)))

(define (lazy-head xs k)
  (if (zero? k)  '()
      (cons (lazy-car xs) (lazy-head (lazy-cdr xs) (- k 1)))))


(define (fuck xs n)
  (if (< n 2) 1
      (* (fuck (- n 1) n))))

(define (lazy-fuck n m)
     (lazy-cons (* n m)  (lazy-fuck (+ n 1) (* n m))))

(define (lazy-ref ls n)
  (if (zero? n) (lazy-car ls)
      (lazy-ref (lazy-cdr ls) (- n 1))))

(define (lazy-factorial n)
  (lazy-ref (lazy-fuck 1 1) (- n 1)))
