

#include "pretty.h"
#include "lexeme.h"
#include "types.h"

#include <stdio.h>
#include <string.h>

void prettyPrint(Lexeme* tree)
{

    if (tree == NULL) return;

    //printf("\nlexeme: ");displayLexeme(tree); printf("\n");
    char* type = getLexemeType(tree);



    if (strcmp(type, PROGRAM) == 0) {
        prettyPrint(car(tree));
        if (cdr(tree) != NULL)
            prettyPrint(cdr(tree));
    }

    else if (strcmp(type, VARDEF) == 0) {
        printf("var ");
        prettyPrint(car(tree));
        prettyPrint(cdr(tree));
        printf(". ");
    }

    else if (strcmp(type, VARASSIGN) == 0) {
        printf(" = ");
        prettyPrint(cdr(tree));
    }

    else if (strcmp(type, FUNCDEF) == 0) {
        printFunction(tree);
    }

    else if (strcmp(type, ACCESS) == 0) {
        prettyPrint(car(tree));
        printf("[");
        prettyPrint(cdr(tree));
        printf("]");
    }

    else if (strcmp(type, CALL) == 0) {
        prettyPrint(car(tree));
        printf("(");
        prettyPrint(cdr(tree));
        printf(")");
    }

    else if (strcmp(type, EXPLIST) == 0) {
        printEXPList(tree);
    }

    else if (strcmp(type, IDLIST) == 0) {
        printIDList(tree);
    }

    else if (strcmp(type, BLOCK) == 0) {
        printBlock(tree);
    }

    else if (strcmp(type, STATEMENTLIST) == 0) {
        printStatements(tree);
    }

    else if (strcmp(type, IFSTATEMENT) == 0) {
        printf("if (");
        prettyPrint(car(tree));
        printf(")");
        prettyPrint(cdr(tree));
    }

    else if (strcmp(type, ELSESTATEMENT) == 0) {
        prettyPrint(car(tree));
        if (cdr(tree) != NULL) {
            printf("else ");
            prettyPrint(cdr(tree));
        }
    }

    else if (strcmp(type, WHILELOOP) == 0) {
        printf("while (");
        prettyPrint(car(tree));
        printf(")");
        prettyPrint(cdr(tree));
    }

    else if (strcmp(type, INTEGER) == 0) {
        printf("%d", getLexemeInt(tree));
    }

    else if (strcmp(type, STRING) == 0) {
        printf("\"%s\"", getLexemeString(tree));
    }

    else if (strcmp(type, BOOLEAN) == 0) {
        printf("%s", getLexemeString(tree));
    }

    else if (strcmp(type, ID) == 0) {
        printf("%s", getLexemeString(tree));
    }

    else if (strcmp(type, OPAREN) == 0) {
        printf("(");
        prettyPrint(cdr(tree));
        printf(")");
    }

    else if (strcmp(type, PRINT) == 0) {
        printf("print (");
        prettyPrint(cdr(tree));
        printf("). ");
    }

    else if (strcmp(type, RETURN) == 0) {
        printf("return ");
        prettyPrint(cdr(tree));
        printf(". ");
    }

    else if (strcmp(type, NOT) == 0) {
        printf("not ");
        prettyPrint(cdr(tree));
    }

    else if (strcmp(type, PLUS) == 0) {
        prettyPrint(car(tree));
        printf(" + ");
        prettyPrint(cdr(tree));
    }

    else if (strcmp(type, MINUS) == 0) {
        prettyPrint(car(tree));
        printf(" - ");
        prettyPrint(cdr(tree));
    }

    else if (strcmp(type, TIMES) == 0) {
        prettyPrint(car(tree));
        printf(" * ");
        prettyPrint(cdr(tree));
    }

    else if (strcmp(type, DIVIDES) == 0) {
        prettyPrint(car(tree));
        printf(" / ");
        prettyPrint(cdr(tree));
    }

    else if (strcmp(type, MODULUS) == 0) {
        prettyPrint(car(tree));
        printf(" %% ");
        prettyPrint(cdr(tree));
    }

    else if (strcmp(type, AND) == 0) {
        prettyPrint(car(tree));
        printf(" and ");
        prettyPrint(cdr(tree));
    }

    else if (strcmp(type, OR) == 0) {
        prettyPrint(car(tree));
        printf(" or ");
        prettyPrint(cdr(tree));
    }

    else if (strcmp(type, EQUALS) == 0) {
        prettyPrint(car(tree));
        printf(" == ");
        prettyPrint(cdr(tree));
    }

    else if (strcmp(type, ASSIGN) == 0) {
        prettyPrint(car(tree));
        printf(" = ");
        prettyPrint(cdr(tree));
        printf(". ");
    }

    else if (strcmp(type, GREATERTHAN) == 0) {
        prettyPrint(car(tree));
        printf(" > ");
        prettyPrint(cdr(tree));
    }

    else if (strcmp(type, LESSTHAN) == 0) {
        prettyPrint(car(tree));
        printf(" < ");
        prettyPrint(cdr(tree));
    }
    else {
        printf("didn't get that!");
    }
}

void printFunction(Lexeme* tree)
{
    printf("def ");
    prettyPrint(car(tree));
    printf("(");
    prettyPrint(car(cdr(tree)));
    printf(")");
    prettyPrint(cdr(cdr(tree)));
}

void printStatements(Lexeme* tree)
{
    while (tree != NULL) {
        prettyPrint(car(tree));
        tree = cdr(tree);
    }
}

void printIDList(Lexeme* tree)
{
    while (tree != NULL) {
        printf("var ");
        prettyPrint(car(tree));
        if (cdr(tree) != NULL)
            printf(", ");
        tree = cdr(tree);
    }
}

void printEXPList(Lexeme* tree)
{
    while (tree != NULL) {
        prettyPrint(car(tree));
        if (cdr(tree) != NULL)
            printf(", ");
        tree = cdr(tree);
    }
}

void printBlock(Lexeme* tree)
{
    if (cdr(tree) != NULL) { //There is a block
        printf(" start ");
        prettyPrint(cdr(tree));
        printf(" stop ");
    }
}
