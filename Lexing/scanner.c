/* Program written by Alex Johnson
/  1/25/2019 - CS 403 - Dr. Lusth
/  scanner.c contains the scanner function for looping through a source file
/  and retrieving the lexemes.
*/

#include "types.h"
#include "lexeme.h"
#include "scanner.h"
#include "lex.h"

#include <stdio.h>
#include <string.h>

int scanner(FILE *fp)
{
    Lexeme* l;
    l = lex(fp);
    while (strcmp(getLexemeType(l), END_OF_INPUT) != 0) {
        displayLexeme(l);
        if (strcmp(getLexemeType(l), ERROR) == 0) return -1;
        l = lex(fp);
    }
    printf("\n");
    return 0;
}
