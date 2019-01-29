#ifndef __PARSER_INCLUDED__
#define __PARSER_INCLUDED__
#include "lexeme.h"
#include <stdio.h>


Lexeme* CurrentLexeme;
FILE* fp;
int parse();
int check(char*);
Lexeme* advance();
Lexeme* match(char*);

// Declare function rules from grammar.txt
void program();
void definition();
void varDef();
void functionDef();
void expression();
void operator();
void unary();
void idDef();
void expressionList();
void optExpressionList();
void argumentList();
void optArgumentList();
void block();
void optStatementList();
void statementList();
void statement();
void ifStatement();
void optElse();
void notOptElse();
void whileLoop();

// Declare function pending rules
int programPending();
int definitionPending();
int varDefPending();
int functionDefPending();
int expressionPending();
int operatorPending();
int unaryPending();
int idDefPending();
int expressionListPending();
int argumentListPending();
int blockPending();
int statementListPending();
int statementPending();
int ifStatementPending();
int notOptElsePending();
int whileLoopPending();

#endif
