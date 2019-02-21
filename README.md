<h1>johnsonscript</h1>
johnsonscript is a dynamically-typed language built on C. It includes features such as:<br/>
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

<h3>Types</h3>
There are currently four types in the language.<br/>
- integers can be declared by: var myInt = 10.<br/>
- strings can be declared by: var myString = "hello world".<br/>
- booleans can be declared by: var myBoolean = True.<br/>
- files can be declared by: var myFile = openfile("filename").<br/>
- arrays can be declared by: var myArray = newarray(size).<br/>

Failing to properly declare variable will lead to an error or potentially a segmentation fault.

<h3>Comments</h3>
Comments are denoted by any line beginning with the '#' character.
Comments are treated as whitespace during lexical analysis.

<h3>Objects</h3>
Objects are declared as if they were a function with only "this." as its body. An example:<br/>
def myTuple(var x, var y) start this. stop<br/>
It can then be constructed by var a = myTuple(2, 4).<br/>

Object attributes are accessed by the '@' symbol. An example:<br/>
var b = a@x.
(b == 2). # True

<h3>Arrays</h3>
Arrays are 0 indexed and treated as any other object. There are three main array functions: <br/>
- newarray(var size) : creates a new array with size elements.<br/>
- getarray(var array, var index) : gets the element from array at index.<br/>
- setarray(var array, var index, var value) : sets the array at index to value.<br/>

<h3>Conditionals</h3>
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
