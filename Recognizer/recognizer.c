#include "types.h"
#include "lexeme.h"
#include "lex.h"
#include "recognizer.h"
#include <unistd.h>

#include <string.h>

Lexeme* CurrentLexeme;

int recognize()
{
    CurrentLexeme = lex(fp);
    program();
    if (strcmp(getLexemeType(CurrentLexeme), ERROR) == 0) {
        printf("Illegal\n");
        displayLexeme(CurrentLexeme);
        return -1;
    }

    match(END_OF_INPUT);
    printf("Legal\n");
    return 0;
}

int check(char* type)
{
    return strcmp(getLexemeType(CurrentLexeme),type) == 0;
}

Lexeme* advance()
{
    Lexeme* prev = CurrentLexeme;
    CurrentLexeme = lex(fp);
    return prev;
}

Lexeme* match(char* type)
{
    // printf("%s ---", type);
    // displayLexeme(CurrentLexeme);
    if (check(type)) {
        return advance();
    }
    else {
        CurrentLexeme = newLexemeError(ERROR, "Syntax Error", LINE);
        return CurrentLexeme;
    }
}

void program()
{
    definition();
    if (programPending())
        program();
}

void definition()
{
    if (varDefPending())
        varDef();
    else
        functionDef();
}

void varDef()
{
    match(VAR);
    match(ID);
    if (check(DOT))
        match(DOT);
    else {
        match(ASSIGN);
        expression();
        match(DOT);
    }
}

void functionDef()
{
    match(DEF);
    match(ID);
    match(OPAREN);
    optArgumentList();
    match(CPAREN);
    block();
}

void expression()
{
    unary();
    if (operatorPending()) {
        operator();
        expression();
    }
}

void operator()
{
    if (check(PLUS))
        match(PLUS);

    else if (check(MINUS))
        match(MINUS);

    else if (check(TIMES))
        match(TIMES);

    else if (check(DIVIDES))
        match(DIVIDES);

    else if (check(MODULUS))
        match(MODULUS);

    else if (check(AND))
        match(AND);

    else if (check(OR))
        match(OR);

    else if (check(EQUALS))
        match(EQUALS);

    else if (check(ASSIGN))
        match(ASSIGN);

    else if (check(GREATERTHAN))
        match(GREATERTHAN);

    else if (check(LESSTHAN))
        match(LESSTHAN);
}

void unary()
{
    if (idDefPending())
        idDef();

    else if (check(INTEGER))
        match(INTEGER);

    else if (check(BOOLEAN))
        match(BOOLEAN);

    else if (check(STRING))
        match(STRING);

    else if (check(OPAREN)) {
        match(OPAREN);
        expression();
        match(CPAREN);
    }

    else if (check(PRINT)) {
        match(PRINT);
        match(OPAREN);
        expression();
        match(CPAREN);
    }

    else if (check(RETURN)) {
        match(RETURN);
        expression();
    }
}

void idDef()
{
    match(ID);

    if (check(OBRACKET)) {
        match(OBRACKET);
        expression();
        match(CBRACKET);
    }

    else if (check(OPAREN)) {
        match(OPAREN);
        optExpressionList();
        match(CPAREN);
    }
}

void expressionList()
{
    expression();
    if (check(COMMA)) {
        match(COMMA);
        expressionList();
    }
}

void optExpressionList()
{
    if (expressionListPending())
        expressionList();
}

void argumentList()
{
    match(ID);
    if (check(COMMA)) {
        match(COMMA);
        argumentList();
    }
}

void optArgumentList()
{
    if (argumentListPending()) {
        argumentList();
    }
}

void block()
{
    match(START);
    optStatementList();
    match(STOP);
}

void optStatementList()
{
    if (statementListPending())
        statementList();
}

void statementList()
{
    statement();
    if (statementListPending())
        statementList();
}

void statement()
{
    if (expressionPending()) {
        expression();
        match(DOT);
    }

    else if (ifStatementPending())
        ifStatement();

    else if (whileLoopPending())
        whileLoop();

    else
        definition();
}

void ifStatement()
{
    match(IF);
    match(OPAREN);
    expression();
    match(CPAREN);
    block();
    optElse();
}

void optElse()
{
    if (notOptElsePending())
        notOptElse();
}

void notOptElse()
{
    match(ELSE);
    if (blockPending())
        block();
    else
        ifStatement();
}

void whileLoop()
{
    match(WHILE);
    match(OPAREN);
    expression();
    match(CPAREN);
    block();
}

// Implement the _Pending functions
int programPending()
{
    return definitionPending();
}

int definitionPending()
{
    return varDefPending() || functionDefPending();
}

int varDefPending()
{
    return check(VAR);
}

int functionDefPending()
{
    return check(DEF);
}

int expressionPending()
{
    return unaryPending();
}

int operatorPending()
{
    return check(PLUS) || check(MINUS) || check(TIMES) || check(DIVIDES)
            || check(MODULUS) || check(AND) || check(OR) || check(EQUALS)
            || check(ASSIGN) || check(GREATERTHAN) || check(LESSTHAN);
}

int unaryPending()
{
    return idDefPending() || check(INTEGER) || check(BOOLEAN) || check(STRING)
            || check(OPAREN) || check(PRINT) || check(RETURN);
}

int idDefPending()
{
    return check(ID);
}

int expressionListPending()
{
    return expressionPending();
}

int argumentListPending()
{
    return check(ID);
}

int blockPending()
{
    return check(START);
}

int statementListPending()
{
    return statementPending();
}

int statementPending()
{
    return expressionPending() || ifStatementPending() || whileLoopPending()
            || definitionPending();
}

int ifStatementPending()
{
    return check(IF);
}

int notOptElsePending()
{
    return check(ELSE);
}

int whileLoopPending()
{
    return check(WHILE);
}
