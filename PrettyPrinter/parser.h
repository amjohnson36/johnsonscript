#ifndef __PARSER_INCLUDED__
#define __PARSER_INCLUDED__
#include "lexeme.h"
#include <stdio.h>


Lexeme* CurrentLexeme;
FILE* fp;
Lexeme* parse();
int check(char*);
Lexeme* advance();
Lexeme* match(char*);

// Declare function rules from grammar.txt
Lexeme* program();
Lexeme* definition();
Lexeme* varDef();
Lexeme* functionDef();
Lexeme* expression();
Lexeme* operator();
Lexeme* unary();
Lexeme* idDef();
Lexeme* expressionList();
Lexeme* optExpressionList();
Lexeme* argumentList();
Lexeme* optArgumentList();
Lexeme* block();
Lexeme* optStatementList();
Lexeme* statementList();
Lexeme* statement();
Lexeme* ifStatement();
Lexeme* optElse();
Lexeme* notOptElse();
Lexeme* whileLoop();

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
