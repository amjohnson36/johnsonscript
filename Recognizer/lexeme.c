/* Program written by Alex Johnson
/  1/25/2019 - CS 403 - Dr. Lusth
/  lexeme.c contains the lexeme object and helper functions, including
/  constructors, variable accessors, and object displayer.
*/

#include "types.h"
#include "lexeme.h"
#include "lex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lexeme
{
    char* type;
    int ival;
    char* sval;

    Lexeme* l;
    Lexeme *r;
} Lexeme;

Lexeme* newLexemeWord(char* type, char* word)
{
    Lexeme* l = malloc(sizeof(Lexeme));
    l->type = malloc(strlen(type)+1);
    strcpy(l->type, type);

    if (strcmp(type,INTEGER) == 0) l->ival = atoi(word);
    else {
        l->sval = malloc(sizeof(word));
        strcpy(l->sval, word);
    }

    return l;
}

Lexeme* newLexemeChar(char* type)
{
    Lexeme* l = malloc(sizeof(Lexeme));
    l->type = malloc(strlen(type)+1);
    strcpy(l->type, type);

    return l;
}

Lexeme* newLexemeError(char* type, char* word, int line)
{
    Lexeme* l = malloc(sizeof(Lexeme));
    l->type = malloc(sizeof(type));
    strcpy(l->type, type);

    l->sval = malloc(sizeof(word));
    strcpy(l->sval, word);

    l->ival = line;
    return l;
}

char* getLexemeType(Lexeme* l)
{
    return l->type;
}

int getLexemeInt(Lexeme* l)
{
    return l->ival;
}

char* getLexemeString(Lexeme* l)
{
    return l->sval;
}

void displayLexeme(Lexeme* l)
{
    printf("%s", l->type);
    if (strcmp(getLexemeType(l), INTEGER) == 0) printf(": %d", getLexemeInt(l));
    if (strcmp(getLexemeType(l), STRING) == 0) printf(": %s", getLexemeString(l));
    if (strcmp(getLexemeType(l), BOOLEAN) == 0) printf(": %s", getLexemeString(l));
    if (strcmp(getLexemeType(l), ID) == 0) printf(": %s", getLexemeString(l));
    if (strcmp(getLexemeType(l), ERROR) == 0) printf(": %s on line %d",
                                                getLexemeString(l), getLexemeInt(l));

    printf("\n");
}
