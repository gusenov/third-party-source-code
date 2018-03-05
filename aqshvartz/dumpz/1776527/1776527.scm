(define (check-integer str)
  (define (helper xs)
    (or
     (null? xs)
     (and (char>=? (car xs) #\0) (char<=? (car xs) #\9) (helper (cdr xs)))))
  
  (let ((n (string->list str)))
    (or
     (and (member (car n) '(#\+ #\-)) (not (null? (cdr n))) (helper (cdr n)))
     (helper n))))

(define (scan-integer str)
  (and (check-integer str) str))

(define (scan-many-integers str)
  (define (string-split str)
    (define len (string-length str))
    
    (define (split a b)
      (cond
        ((>= b len) (if (= a b) '() (cons (substring str a b) '())))
        ((char-whitespace? (string-ref str b)) (if (= a b)
                                                   (split (+ 1 a) (+ 1 b))
                                                   (cons (substring str a b) (split b b))))
        (else (split a (+ 1 b)))))
    
    (split 0 0))
  
  (define (str->int str)
    (and (check-integer str)
         (let ((n (string->list str)))
           (cond
             ((equal? (car n) #\-) (- (helper (reverse (cdr n)) 1)))
             ((equal? (car n) #\+) (helper (reverse (cdr n)) 1))
             (else (helper (reverse n) 1))))))

  (define (helper xs p)
    (or
     (and (null? xs) 0)
     (+ (* (- (char->integer (car xs)) (char->integer #\0)) p) (helper (cdr xs) (* p 10)))))
  
  (let ((answer (map str->int (string-split str))))
    (and (not (member #f answer)) answer)))