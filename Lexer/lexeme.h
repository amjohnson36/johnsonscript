/* Program written by Alex Johnson
/  1/25/2019 - CS 403 - Dr. Lusth
/  lexeme.h contains function declarations for the lexeme.c file.
*/

#ifndef __LEXEME_INCLUDED__
#define __LEXEM_INCLUDED__

typedef struct lexeme Lexeme;

Lexeme* newLexemeWord(char*,char*);
Lexeme* newLexemeChar(char*,char);
Lexeme* newLexemeError(char*,char*,int);
char* getLexemeType(Lexeme*);
int getLexemeInt(Lexeme*);
void displayLexeme(Lexeme*);

#endif
