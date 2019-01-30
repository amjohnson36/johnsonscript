/* Program written by Alex Johnson
/  1/25/2019 - CS 403 - Dr. Lusth
/  lex.h contains function declarations for the lex.c file.
*/

#ifndef __LEX_INCLUDED__
#define __LEX_INCLUDED__

#include <stdio.h>

Lexeme* lex(FILE*);
Lexeme* lexNumber(FILE*);
Lexeme* lexVariableOrKeyword(FILE*);
Lexeme* lexString(FILE*);
void skipWhiteSpace(FILE*);

#endif
