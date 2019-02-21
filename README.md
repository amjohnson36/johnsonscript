# johnsonscript
johnsonscript is a dynamically-typed language built on C. It includes features such as:
- multiple types
- comments
- objects
- arrays with O(1) access time
- conditionals
- recursion
- iteration
- command line arguments
- printing to console
- reading integers from file
- numerous operators
- anonymous functions
- functions as first class objects

The proper file extension is ".johns". The interpreter can be executed through the command:

$ johnsonscript myfile.johns

after building the executable.

## Types
There are currently five types in the language:
- integers
- strings
- booleans
- files
- arrays

Below are some examples of declaring new variables of each type.
```
var myInt = 10.
var myString = "hello world".
var myBoolean = True.
var myFile = openfile("filename").
var myArray = newarray(size).
```

Failing to properly declare variables will lead to an error or potentially a segmentation fault.


## Comments
Comments are denoted by any line beginning with the '#' character.
Comments are treated as whitespace during lexical analysis.


## Objects
Objects are declared as if they were a function with only "this." as its body. An example:
```
def myTuple(var x, var y)
start
    this.
stop
```
It can then be constructed by:
```
var a = myTuple(2, 4).
```

Object attributes are accessed by the '@' symbol. An example:
```
var b = a@x.
(b == 2). # True

a@x = 15.
```

## Arrays
Arrays are 0 indexed and are treated as any other object. There are three main array functions:
- newarray(var size) : creates a new array with size elements.
- getarray(var array, var index) : gets the element from array at index.
- setarray(var array, var index, var value) : sets the array at index to value.


## Conditionals
The following conditionals are supported:
- if (expression)
- else if (expression)
- else
- while (expression)

They are then followed by a block of statements.

## Recursion
Recursion is naturally built into the language. The return value for a function is simply the last statement processed so setting a variable equal to the value is sufficient. An example of recursion:
```
def fib(var n)
start
    if (n == 0) start
        var return = 0.
    stop

    else if (n == 1) start
         var return = 1.
    stop

    else start
        var return = fib(n-1) + fib(n-2).
    stop
stop
```

## Iteration
A while loop is the only way to implement iteration within the language. An example:
```
def printNums(var n)
start
    var i = 0.
    while (i < n) start
        print(i + \n). # newline character doesn't have quotations surrounding
        i = i + 1.
    stop
stop
```

## Command Line Arguments
There are two built in functions for dealing with command line arguments:
- getargcount() : returns the number of command line arguments
- getarg(var index) : returns the string value of the command line argument at index (0 based)

## Printing
The function for printing to console is:
- print(expression)

Note that string concatenation is built into the + operator, and that the newline character is \n without and quotes.
```
var s1 = "hello,".
var s2 = "world!".
var num = 1.
print(s1 + " " + s2 + " " + num + \n). # will print "hello, world! 1"
```


## Files
There are four built in functions for dealing with files:
- openfile(var fname) : opens the file with name == fname
- readinteger(var fp) : reads one integer from the opened file fp
- atfileend(var fp) : checks if the opened file fp has reached its end
- closefile(var fp) : closes the opened file fp



## Operators
There are many operators build into the language:
- \+  addition
- \-  subtraction
- \*  multiplication
- \\  division
- %   modulus
- = assign
- == equals
- \> greater than
- < less than
- and
- or
- not


## Anonymous Functions
Anonymous functions are declared using the lambda keyword. An example:
```
lambda (x)
start
    x * 2.
stop
```

## Functions
Functions are treated as first class objects, such as in scheme. This means that you can assign variables equal to them. An example:
```
def f(var x)
start
    def g(var y) start x + y. stop
stop

var a = f(3).
a(5). # Evaluates to 8
```
