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

<h2> Environment Functions </h2>
The following functions are used in the Environment milestone:<br/>

<h3> envDemo() </h3>
Returns an instance of an environment demo. Shows off all the functions used in environment such as 
making a new environment, inserting, extending, and updating.

<h3> newEnvironment() </h3>
Returns a new environment lexeme for storing variables. Initially the left pointer is an empty table and the right pointer is null.

<h3> insertEnvironment(Lexeme* env, Lexeme* id, Lexeme* value) </h3>
Inserts the given variable and its value into the specified environment. The id is inserted as a new ID on the left pointer of the table and the value
is inserted as a new [type] on the right side of the table. The inserted value is returned.

<h3> getVal(Lexeme* env, Lexeme* id) </h3>
Searches through the environment scope to find the matching ID. When that ID is found, the value associated with that ID is returned. If it is not found an error will be thrown.

<h3> updateVal(Lexeme* env, Lexeme* id, Lexeme* val) </h3>
Searches through the environment scope to find the matching ID. When that ID is found, the value associated with that ID is updated to val. If it is not found an error will be thrown.

<h3> extend(Lexeme* env, Lexeme* vars, Lexeme* vals) </h3>
Extends the current environment to a new scope. All of the variables in the current environment are also copied over into the new environment so that functions can use variables in 
the outer scope but not vice versa.
 
<h3> displayEnvironment(Lexeme* env) </h3>
Goes through the environments starting at the innermost scope and displays all the variables and their values associated with them.

