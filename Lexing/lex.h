#ifndef __LEX_INCLUDED__
#define __LEX_INCLUDED__

#include <stdio.h>

Lexeme* lex(FILE*);
Lexeme* lexNumber(FILE*);
Lexeme* lexVariableOrKeyword(FILE*);
Lexeme* lexString(FILE*);
void skipWhiteSpace(FILE*);

#endif
