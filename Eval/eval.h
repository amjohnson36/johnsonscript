#ifndef __EVAL_INCLUDED__
#define __EVAL_INCLUDED__

#include "lexeme.h"
#include "types.h"

Lexeme* eval(Lexeme* tree, Lexeme* env);

// Function defs
Lexeme* evalFuncDef(Lexeme* tree, Lexeme* env);
Lexeme* getFuncDefParams(Lexeme* tree);
Lexeme* getFuncDefBody(Lexeme* tree);
Lexeme* getFuncDefName(Lexeme* tree);

// Function calls
Lexeme* evalFuncCall(Lexeme* tree, Lexeme* env);
Lexeme* getFuncCallName(Lexeme* tree);
Lexeme* getFuncCallArgs(Lexeme* tree);
Lexeme* getClosureParams(Lexeme* closure);
Lexeme* getClosureBody(Lexeme* closure);
Lexeme* getClosureEnvironment(Lexeme* closure);
Lexeme* evalArgs(Lexeme* args, Lexeme* env);
Lexeme* evalPrint(Lexeme*, Lexeme*);
Lexeme* evalReturn(Lexeme*, Lexeme*);

Lexeme* evalBlock(Lexeme* tree, Lexeme* env);

// Operations
Lexeme* evalPlus(Lexeme* tree, Lexeme* env);
Lexeme* evalMinus(Lexeme* tree, Lexeme* env);
Lexeme* evalTimes(Lexeme* tree, Lexeme* env);
Lexeme* evalDivides(Lexeme* tree, Lexeme* env);
Lexeme* evalModulus(Lexeme* tree, Lexeme* env);
Lexeme* evalEquals(Lexeme* tree, Lexeme* env);
Lexeme* evalGreaterThan(Lexeme* tree, Lexeme* env);
Lexeme* evalLessThan(Lexeme* tree, Lexeme* env);
Lexeme* evalAssign(Lexeme* tree, Lexeme* env);

Lexeme* evalAnd(Lexeme* tree, Lexeme* env);
Lexeme* evalOr(Lexeme* tree, Lexeme* env);
Lexeme* evalNot(Lexeme* tree, Lexeme* env);

Lexeme* evalAt(Lexeme* tree, Lexeme* env);

Lexeme* evalVarDef(Lexeme* tree, Lexeme* env);

Lexeme* evalIf(Lexeme* tree, Lexeme* env);
Lexeme* evalWhile(Lexeme* tree, Lexeme* env);


#endif
