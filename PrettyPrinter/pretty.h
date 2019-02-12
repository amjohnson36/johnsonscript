#ifndef __PRETTY_INCLUDED__
#define __PRETTY_INCLUDED__


#include "lexeme.h"

void prettyPrint(Lexeme*);
void printFunction(Lexeme*);
void printStatements(Lexeme*);
void printIDList(Lexeme*);
void printEXPList(Lexeme*);
void printBlock(Lexeme*);

#endif
