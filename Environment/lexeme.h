/* Program written by Alex Johnson
/  2/10/2019 - CS 403 - Dr. Lusth
/  lexeme.h contains function declarations for the lexeme.c file.
*/

#ifndef __LEXEME_INCLUDED__
#define __LEXEME_INCLUDED__

typedef struct lexeme Lexeme;

Lexeme* newLexemeWord(char*,char*);
Lexeme* newLexemeChar(char*);
Lexeme* newLexemeError(char*,char*,int);
char* getLexemeType(Lexeme*);
int getLexemeInt(Lexeme*);
char* getLexemeString(Lexeme*);
void displayLexeme(Lexeme*);

// Environment functions
Lexeme* cons(char*,Lexeme*,Lexeme*);
void setCar(Lexeme*,Lexeme*);
void setCdr(Lexeme*,Lexeme*);
Lexeme* car(Lexeme*);
Lexeme* cdr(Lexeme*);

#endif
