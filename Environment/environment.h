

#ifndef __ENVIRONMENT_INCLUDED__
#define __ENVIRONMENT_INCLUDED__

#include "lexeme.h"

int envDemo();
Lexeme* newEnvironment();
Lexeme* insertEnvironment(Lexeme*,Lexeme*,Lexeme*);
Lexeme* getVal(Lexeme*, Lexeme*);
Lexeme* updateVal(Lexeme*, Lexeme*, Lexeme*);
Lexeme* extend(Lexeme*,Lexeme*,Lexeme*);
void displayEnvironment(Lexeme*);



#endif
