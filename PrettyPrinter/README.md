<h2>Introduction</h2>
This is the rough draft of the README.md file for the johnsonScript programming language.
This is a dynamically-typed language built upon C.

<h2>Types</h2>
There are currently three types in the language.<br/>
-Integers are declared by: var myInt = 10.<br/>
-Strings are declared by: var myString = "hello world".<br/>
-Booleans are declared by: var myBoolean = True.<br/>

Failing to properly set variables equal to a valid type will lead to an error.

<h2>Comments</h2>
Comments are denoted by any line beginning with the '#' character. To do multiline comments, just type a '#' at the start of each line.
Comments are treated as whitespace during lexical analysis.

<h2>Declarations</h2>
There are two things to be declared in the johnsonScript language: variables and functions.<br/>
-Variables are declared by var ID = value. or just var ID.<br/>
-Functions are declared by def ID(optional arguments). It is then usually followed by a block that begins with start and ends with stop.<br/>

<h2>Operators</h2>
The following operators are supported:<br/>
-PLUS +<br/>
-MINUS -<br/>
-TIMES * <br/>
-DIVIDES / <br/> 
-MODULUS % <br/>
-NOT not <br/>
-AND and <br/>
-OR or <br/>
-EQUALS == <br/>
-ASSIGN = <br/>
-GREATERTHAN > <br/>
-LESSTHAN < <br/>

<h2>Filetypes</h2>
The correct file extension for the language is the .johns extension.

<h2>Building</h2>
The makefile currently accepts the following commands:<br/>
-make: builds the project into the executable<br/>
-make run: builds the project and runs 5 tests. test5.johns is designed to fail

<h2> Pretty Printer Test Filess </h2>
The following test files are provided in the Pretty Printer milestone and are run with $make testx:<br/>

<h3> test1 </h3>
Expected output (no newline): <br/>
def equals(var a, var b) start if (a == b) start return True.  stop else  
start return False.  stop  stop 

<h3> test2 </h3>
Expected output (no newline): <br/>
def fizzBuzz() start var number = 1. while (number < 100) start if 
((number % 3 == 0) and (number % 5 == 0)) start print ("FizzBuzz").  
stop else if (number % 3 == 0) start print ("Fizz").  stop else if 
(number % 5 == 0) start print ("Buzz").  stop else  start print (number).  stop 
print ("\n"). number = number + 1.  stop  stop 

<h3> test3 </h3>
Expected output (no newline): <br/>
def recursiveFib(var number) start if (number == 0) start return 0.  
stop if (number == 1) start return 1.  stop return 
recursiveFib(number - 1) + recursiveFib(number - 2).  stop 
