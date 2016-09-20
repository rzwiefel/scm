; map a function over a list
(define map (lambda (fn ls)
  (if (null? ls)
        ls ; base case
        (cons
          (fn (car ls))
          (map fn (cdr ls))))))

; filter items from a list
(define filter (lambda (fn ls)
  (if (null? ls)
    ls 
    (if (fn (car ls))
      (cons (car ls) (filter fn (cdr ls)))
      (filter fn (cdr ls))))))

; reverse a list
(define reverse (lambda (ls)
  (begin
    (define reverse-inner (lambda (ls acc)
      (if (null? ls)
        acc
        (reverse-inner (cdr ls) (cons (car ls) acc)))))
    (reverse-inner ls '()))))

(define concat (lambda (ls value)
  (if (null? ls)
    value
    (cons (car ls) (concat (cdr ls) value)))))

(define append (lambda (ls value)
  (concat ls (cons value '()))))

(define inc (lambda (x) (+ x 1)))

; invert a boolean value
(define not
  (lambda (x) (if x #f #t)))

(print (map inc (concat '(1 2 3 4 5) '(6 7 8 9 10))))

