/* Program written by Alex Johnson
/  2/10/2019 - CS 403 - Dr. Lusth
/  environment.h contains variable declarations for the environment.c file.
*/

#ifndef __ENVIRONMENT_INCLUDED__
#define __ENVIRONMENT_INCLUDED__

#include "lexeme.h"

int envDemo();
Lexeme* newEnvironment();
Lexeme* insertEnvironment(Lexeme*,Lexeme*,Lexeme*);
Lexeme* getVal(Lexeme*, Lexeme*);
Lexeme* updateVal(Lexeme*, Lexeme*, Lexeme*);
Lexeme* extend(Lexeme*,Lexeme*,Lexeme*);
void displayEnvironment(Lexeme*, int);



#endif
