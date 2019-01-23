#include "types.h"
#include "lexeme.h"
#include "scanner.h"
#include "lex.h"

#include <stdio.h>
#include <string.h>

void scanner(FILE *fp)
{
    Lexeme* l;
    l = lex(fp);
    while (strcmp(getLexemeType(l), END_OF_INPUT) != 0) {
        displayLexeme(l);
        l = lex(fp);
    }
}
