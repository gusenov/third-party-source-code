(define error 1)

(define (tokenize str)
  ;
  (define (ret-var i)
    (or
     (and (< i (string-length str)) (char-alphabetic? (string-ref str i)) (ret-var (+ i 1)))
     i))
  ;
  (define (ret-num i)
    (if (< i (string-length str))
        (let ((lexem (string-ref str i)))
          (cond
            ((char-numeric? lexem) (ret-num (+ i 1)))
            ((member lexem '(#\e #\E)) (if (member (string-ref str (+ i 1)) '(#\+ #\-)) (ret-num (+ i 2)) (ret-num (+ i 1))))
            ((equal? lexem #\.) (ret-num (+ i 1)))
            (else i)))
        i))
  ;
  (define (helper i)
    (or
     (and (= i (string-length str)) '())
     (let ((lexem (string-ref str i)))
       (cond
         ((member lexem '(#\( #\))) (cons (string lexem) (helper (+ i 1))))
         ((member lexem '(#\+ #\- #\/ #\* #\^)) (cons (string->symbol (string lexem)) (helper (+ i 1))))
         ((char-alphabetic? lexem) (let ((j (ret-var i))) (cons (string->symbol (substring str i j)) (helper j))))
         ((char-numeric? lexem) (let ((j (ret-num i))) (cons (string->number (substring str i j)) (helper j))))
         ((char-whitespace? lexem) (helper (+ i 1)))
         (else (error #f))))))
  
  (call-with-current-continuation
   (lambda (exit)
     (set! error exit)
     (helper 0))))

(define (parse tokens)
  (define (peek) (if (null? tokens) #f (car tokens)))
  (define (next)
    (let ((answer (peek)))
      (if answer
          (set! tokens (cdr tokens)))
      answer))
  ;
  (define (parse-expr)
    ;
    (define (helper buffer)
      (let ((lx (peek)))
        (if (member lx '(+ -))
            (helper (list buffer (next) (parse-term)))
            buffer)))
    
    (helper (parse-term)))
  ;
  (define (parse-term)
    ;
    (define (helper buffer)
      (let ((lx (peek)))
        (if (member lx '(* /))
            (helper (list buffer (next) (parse-power)))
            buffer)))
    
    (helper (parse-power)))
  ;
  (define (parse-power)
    (let ((buffer (parse-factor)))
      (if (equal? (peek) '^)
          (list buffer (next) (parse-power))
          buffer)))
  
  (define (parse-factor)
    (let ((lx (next)))
      (cond ((number? lx) lx)
            ((equal? lx "(") (let ((answer (parse-expr)))
                               (if (equal? (next) ")")
                                   answer
                                   (error #f))))
            ((equal? lx '-) (list '- (parse-factor)))
            ((and (symbol? lx) (not (member lx '(+ * / =)))) lx)
            (else (error #f)))))
  
  (call-with-current-continuation
   (lambda (exit) 
     (set! error exit)
     (let ((answer (parse-expr)))
       (and (not (next)) answer)))))

(define (tree->scheme expr)
  (if (and (list? expr) (= (length expr) 3))
      (let ((x (car expr))
            (op (cadr expr))
            (y (caddr expr)))
        (list (or (and (equal? op '^) 'expt) op) (tree->scheme x) (tree->scheme y)))
      expr))