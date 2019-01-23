#ifndef __LEXEME_INCLUDED__
#define __LEXEM_INCLUDED__

typedef struct lexeme Lexeme;

Lexeme* newLexemeWord(char*,char*);
Lexeme* newLexemeChar(char*,char);
char* getLexemeType(Lexeme*);
int getLexemeInt(Lexeme*);
double getLexemeReal(Lexeme*);
void displayLexeme(Lexeme*);

#endif
