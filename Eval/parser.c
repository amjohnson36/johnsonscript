#include "types.h"
#include "lexeme.h"
#include "lex.h"
#include "parser.h"
#include <unistd.h>

#include <string.h>
#include <stdlib.h>

Lexeme* CurrentLexeme;

Lexeme* parse()
{
    Lexeme* tree;
    CurrentLexeme = lex(fp);
    tree = program();
    match(END_OF_INPUT);
    return tree;
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
    if (check(type)) {
        return advance();
    }
    else if (strcmp(getLexemeType(CurrentLexeme), ERROR) == 0) {
        printf("\nIllegal\n");
         displayLexeme(CurrentLexeme);
         printf("\n");
         exit(-1);
    }
    else {
        printf("\nIllegal\n");
        char* ftype = getLexemeType(CurrentLexeme);
        CurrentLexeme = newLexemeError(ERROR, "Syntax Error", LINE);
        displayLexeme(CurrentLexeme);
        printf("\nexpected %s, found %s\n", type, ftype);
        exit(-1);
    }
}

Lexeme* program()
{
    Lexeme* d;
    Lexeme* p;
    if (definitionPending())
        d = definition();
    else if (statementPending())
        d = statement();

    if (programPending())
        p = program();
    else
        p = NULL;
    return cons(PROGRAM, d, p);
}

Lexeme* definition()
{
    if (varDefPending())
        return varDef();
    else
        return functionDef();
}

Lexeme* varDef()
{
    Lexeme* i;
    Lexeme* e;
    match(VAR);
    i = match(ID);
    if (check(DOT)) {
        match(DOT);
        e = NULL;
    }

    else {
        match(ASSIGN);
        e = expression();
        e = cons(VARASSIGN, NULL, e);
        match(DOT);
    }
    return cons(VARDEF, i, e);
}

Lexeme* functionDef()
{
    Lexeme* i;
    Lexeme* a;
    Lexeme* b;

    match(DEF);
    i = match(ID);
    match(OPAREN);
    a = optParamList();
    match(CPAREN);
    b = block();

    return cons(FUNCDEF, i, cons(JUNK, a, b));
}

Lexeme* expression()
{
    Lexeme* u;
    Lexeme* o;
    Lexeme* e;

    u = unary();
    if (operatorPending()) {
        o = operator();
        e = expression();
        return cons(getLexemeType(o), u, e);
    }
    else
        return u;
}

Lexeme* operator()
{
    if (check(PLUS))
        return match(PLUS);

    else if (check(MINUS))
        return match(MINUS);

    else if (check(TIMES))
        return match(TIMES);

    else if (check(DIVIDES))
        return match(DIVIDES);

    else if (check(MODULUS))
        return match(MODULUS);

    else if (check(AND))
        return match(AND);

    else if (check(OR))
        return match(OR);

    else if (check(EQUALS))
        return match(EQUALS);

    else if (check(ASSIGN))
        return match(ASSIGN);

    else if (check(GREATERTHAN))
        return match(GREATERTHAN);

    else if (check(LESSTHAN))
        return match(LESSTHAN);

    else
        return NULL;
}

Lexeme* unary()
{
    Lexeme* tree;

    if (idDefPending())
        return idDef();

    else if (check(INTEGER))
        return match(INTEGER);

    else if (check(BOOLEAN))
        return match(BOOLEAN);

    else if (check(STRING))
        return match(STRING);

    else if (check(OPAREN)) {
        match(OPAREN);
        tree = expression();
        match(CPAREN);
        return cons(OPAREN, NULL, tree);
    }

    else if (check(PRINT)) {
        match(PRINT);
        match(OPAREN);
        tree = expression();
        match(CPAREN);
        return cons(PRINT, NULL, tree);
    }

    else if (check(NOT)) {
        match(NOT);
        tree = unary();
        return cons(NOT, NULL, tree);
    }

    else if (check(NEGATIVE)) {
        match(NEGATIVE);
        tree = unary();
        return cons(NEGATIVE, NULL, tree);
    }

    // Built in array functions
    else if (check(NEWARRAY)) {
        match(NEWARRAY);
        match(OPAREN);
        tree = expressionList();
        match(CPAREN);
        return cons(NEWARRAY, NULL, tree);
    }

    else if (check(GETARRAY)) {
        match(GETARRAY);
        match(OPAREN);
        tree = expressionList();
        match(CPAREN);
        return cons(GETARRAY, NULL, tree);
    }

    else if (check(SETARRAY)) {
        match(SETARRAY);
        match(OPAREN);
        tree = expressionList();
        match(CPAREN);
        return cons(SETARRAY, NULL, tree);
    }

    // built in arg functions
    else if (check(GETARGCOUNT)) {
        match(GETARGCOUNT);
        match(OPAREN);
        match(CPAREN);
        return cons(GETARGCOUNT, NULL, NULL);
    }

    else if (check(GETARG)) {
        match(GETARG);
        match(OPAREN);
        tree = expressionList();
        match(CPAREN);
        return cons(GETARG, NULL, tree);
    }

    else if (check(OPENFILE)) {
        match(OPENFILE);
        match(OPAREN);
        tree = expressionList();
        match(CPAREN);
        return cons(OPENFILE, NULL, tree);
    }

    else if (check(READINTEGER)) {
        match(READINTEGER);
        match(OPAREN);
        tree = expressionList();
        match(CPAREN);
        return cons(READINTEGER, NULL, tree);
    }

    else if (check(ATFILEEND)) {
        match(ATFILEEND);
        match(OPAREN);
        tree = expressionList();
        match(CPAREN);
        return cons(ATFILEEND, NULL, tree);
    }

    else if (check(CLOSEFILE)) {
        match(CLOSEFILE);
        match(OPAREN);
        tree = expressionList();
        match(CPAREN);
        return cons(CLOSEFILE, NULL, tree);
    }

    else
        return NULL;
}

Lexeme* idDef()
{
    Lexeme* i;
    Lexeme* a;
    i = match(ID);

    if (check(OBRACKET)) {
        match(OBRACKET);
        a = expression();
        match(CBRACKET);

        return cons(ACCESS, i, a);
    }

    else if (check(OPAREN)) {
        match(OPAREN);
        a = optExpressionList();
        match(CPAREN);
        return cons(CALL, i, a);
    }

    else if (check(AT)) {
        match(AT);
        a = idDef();
        return cons(AT, i, a);
    }

    else
        return i;
}

Lexeme* expressionList()
{
    Lexeme* e;
    Lexeme* l;
    e = expression();
    if (check(COMMA)) {
        match(COMMA);
        l = expressionList();
    }
    else
        l = NULL;
    return cons(EXPLIST, e, l);
}

Lexeme* optExpressionList()
{
    if (expressionListPending())
        return expressionList();
    else
        return NULL;
}

Lexeme* paramList()
{
    Lexeme* i;
    Lexeme* a;
    match(VAR);
    i = match(ID);
    if (check(COMMA)) {
        match(COMMA);
        a = paramList();
    }
    else a = NULL;
    return cons(IDLIST, i, a);
}

Lexeme* optParamList()
{
    if (paramListPending()) {
        return paramList();
    }
    else
        return NULL;
}

Lexeme* block()
{
    Lexeme* s;
    match(START);
    s = optStatementList();
    match(STOP);
    return cons(BLOCK, NULL, s);
}

Lexeme* optStatementList()
{
    if (statementListPending())
        return statementList();
    else
        return NULL;
}

Lexeme* statementList()
{
    Lexeme *s;
    Lexeme* l;
    s = statement();
    if (statementListPending())
        l = statementList();
    else
        l = NULL;
    return cons(STATEMENTLIST, s, l);
}

Lexeme* statement()
{
    if (expressionPending()) {
        Lexeme* e = expression();
        match(DOT);
        return e;
    }

    else if (ifStatementPending())
        return ifStatement();

    else if (whileLoopPending())
        return whileLoop();

    else
        return definition();
}

Lexeme* ifStatement()
{
    Lexeme* e;
    Lexeme* b;
    Lexeme* o;
    match(IF);
    match(OPAREN);
    e = expression();
    match(CPAREN);
    b = block();
    o = optElse();

    return cons(IFSTATEMENT, e, cons(ELSESTATEMENT, b, o));
}

Lexeme* optElse()
{
    if (notOptElsePending())
        return notOptElse();
    else
        return NULL;
}

Lexeme* notOptElse()
{
    match(ELSE);
    if (blockPending())
        return block();
    else
        return ifStatement();
}

Lexeme* whileLoop()
{
    Lexeme* e;
    Lexeme* b;
    match(WHILE);
    match(OPAREN);
    e = expression();
    match(CPAREN);
    b = block();
    return cons(WHILELOOP, e, b);
}

// Implement the _Pending functions
int programPending()
{
    return definitionPending() || statementPending();
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
            || check(OPAREN) || check(PRINT) || check(NEWARRAY) || check(SETARRAY)
            || check(GETARRAY) || check(GETARGCOUNT) || check(GETARG) || check(OPENFILE)
            || check(READINTEGER) || check(ATFILEEND) || check(CLOSEFILE) || check(NEGATIVE);
}

int idDefPending()
{
    return check(ID);
}

int expressionListPending()
{
    return expressionPending();
}

int paramListPending()
{
    return check(VAR);
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
