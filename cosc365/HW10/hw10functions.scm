; Noah Morris
; nmorri11

; swap function that take in two values and places them into a cons pair with the smallest number first
(define (swap num1 num2)
   ; determines which number is smaller and should be outputted first
   (if (> num1 num2)
       (cons num2 num1)
       (cons num1 num2)))

; sum function that sums up every value from within a list (from coding in scheme examples)
(define (sum x)
    (if (null? x)
       0
       (+ (car x) (sum (cdr x)))))

; length function that returns the length of a list (from coding in scheme examples)
(define (list-length x)
    (if (null? x)
       0
       (+ 1 (list-length (cdr x)))))

; avg function that gets the average of the values within a list, uses the sum and list-length functions from the examples to perform the division required to find the average
(define (avg list)
   (+ 0.0(/ (sum list) (list-length list))))

; max function that finds the largest number within a list and returns it
(define (max list)
   (cond
     ; if there is nothing beyond the first index of the list, then return the first index
     ((null? (cdr list))
        (car list))
     ; if the first index is less than the one after it, run the function recursively without the first index
     ((< (car list) (car (cdr list)))
        (max (cdr list)))
     ; else recursively run the function with the second index removed from the list
     (else (max (cons (car list) (cdr (cdr list)))))))

; increasing function that takes in multiple arguments and returns either true or false to if the arguments are in numerical order or not
(define (increasing . args)
   (cond
     ; if the number of arguments is one, return true
     ((eq? (length args) 1)
        #t)
     ; if the first argument is less than or equal to the second argument
     ((<= (car args) (car (cdr args)))
        ;recursively run through the function again, but with the first argument being removed if true
        (apply increasing (cdr args)))
     ; else, return false
     (else #f)))

; apowb function that takes two arguments and performs the operation num1^num2
(define (apowb num1 num2)
   ; if num2 is zero, then return 1
   (if(zero? num2) 
      1
   ; recursively run apowb with num2 having 1 subtracted to multiply num1 by itself until num2 is zero
   (* num1 (apowb num1 (- num2 1)))))

; filter function that takes uses lambda to take in a predicate and list to take out everything in the list that the predicate calls for
(define filter (lambda (predicate list)
  (cond 
    ; if the list is empty, return an empty list
    ((null? list)
       '())
    ; if the first index fulfills the conditions of the predicate, keep the hold onto the first index and perform recursion with the rest of the list
    ((predicate (car list))
       (cons (car list) (filter predicate (cdr list))))
    ; else perform recursion with the list minus the first index
    (else (filter predicate (cdr list))))))