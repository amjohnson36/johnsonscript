#include "types.h"
#include "lexeme.h"
#include "scanner.h"
#include "lex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lexeme
{
    char* type;
    int ival;
    char* sval;
    double rval;

} Lexeme;

Lexeme* newLexemeWord(char* type, char* word)
{
    Lexeme* l = malloc(sizeof(Lexeme));
    l->type = malloc(sizeof(type));
    strcpy(l->type, type);

    if (strcmp(type,INTEGER) == 0) l->ival = atoi(word);
    else if (strcmp(type,REAL) == 0) l->rval = atof(word);
    else {
        l->sval = malloc(sizeof(word));
        strcpy(l->sval, word);
    }

    return l;
}

Lexeme* newLexemeChar(char* type, char word)
{
    Lexeme* l = malloc(sizeof(Lexeme));
    l->type = malloc(sizeof(type));
    strcpy(l->type, type);
    l->sval = malloc(word);
    //l->sval = word;

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

double getLexemeReal(Lexeme* l)
{
    return l->rval;
}

char* getLexemeString(Lexeme* l)
{
    return l->sval;
}

void displayLexeme(Lexeme* l)
{
    printf("%s", l->type);
    if (strcmp(getLexemeType(l), INTEGER) == 0) printf(": %d", getLexemeInt(l));
    if (strcmp(getLexemeType(l), REAL) == 0) printf(": %lf", getLexemeReal(l));
    if (strcmp(getLexemeType(l), STRING) == 0) printf(": %s", getLexemeString(l));
    printf("\n");
}
