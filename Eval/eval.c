

#include "eval.h"
#include "lexeme.h"
#include "types.h"
#include "environment.h"
#include "lex.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Lexeme* eval(Lexeme* tree, Lexeme* env)
{

    if (tree == NULL) return NULL;

    printf("\nlexeme: ");displayLexeme(tree); printf("\n");
    char* type = getLexemeType(tree);

    // Simple types, return the tree
    if (strcmp(type, INTEGER) == 0) {
        return tree;
    }

    else if (strcmp(type, STRING) == 0) {
        return tree;
    }

    else if (strcmp(type, BOOLEAN) == 0) {
        return tree;
    }

    // ID, return the value
    else if (strcmp(type, ID) == 0) {
        return getVal(env, tree);
    }

    // Operators
    else if (strcmp(type, PLUS) == 0) {
        return evalPlus(tree, env);
    }

    else if (strcmp(type, MINUS) == 0) {
        return evalMinus(tree, env);
    }

    else if (strcmp(type, TIMES) == 0) {
        return evalTimes(tree, env);
    }

    else if (strcmp(type, DIVIDES) == 0) {
        return evalDivides(tree, env);
    }

    else if (strcmp(type, MODULUS) == 0) {
        return evalModulus(tree, env);
    }

    else if (strcmp(type, EQUALS) == 0) {
        return evalEquals(tree, env);
    }

    else if (strcmp(type, GREATERTHAN) == 0) {
        return evalGreaterThan(tree, env);
    }

    else if (strcmp(type, LESSTHAN) == 0) {
        return evalLessThan(tree, env);
    }

    // AND and OR short-circuit
    else if (strcmp(type, AND) == 0) {
        return evalAnd(tree, env);
    }

    else if (strcmp(type, OR) == 0) {
        return evalOr(tree, env);
    }

    else if (strcmp(type, NOT) == 0) {
        return evalNot(tree, env);
    }

    // Object access is @
    else if (strcmp(type, AT) == 0) {
        return evalAt(tree, env);
    }

    // Assign operator evals rhs for sure
    // Lhs is a variable or @ expression
    else if (strcmp(type, ASSIGN) == 0) {
        return evalAssign(tree, env);
    }

    else if (strcmp(type, VARDEF) == 0) {
        return evalVarDef(tree, env);
    }

    else if (strcmp(type, VARASSIGN) == 0) {
        return evalVarDef(tree, env);
    }

    else if (strcmp(type, FUNCDEF) == 0) {
        return evalFuncDef(tree, env);
    }

    else if (strcmp(type, IFSTATEMENT) == 0) {
        return evalIf(tree, env);
    }

    else if (strcmp(type, WHILELOOP) == 0) {
        return evalWhile(tree, env);
    }

    else if (strcmp(type, CALL) == 0) {
        return evalFuncCall(tree, env);
    }

    else if (strcmp(type, BLOCK) == 0) {
        return evalBlock(tree, env);
    }

    else if (strcmp(type, PROGRAM) == 0) {
        eval(car(tree), env);
        return eval(cdr(tree), env);
    }

    else {
        printf("didn't get that!");
        return NULL;
    }
}

// Functions for evaluating Function definitions
Lexeme* evalFuncDef(Lexeme* tree, Lexeme* env)
{
    Lexeme* closure = cons(CLOSURE, env,
                        cons(JOIN, getFuncDefParams(tree),
                            cons(JOIN, getFuncDefBody(tree), NULL)));
    return insertEnvironment(env, getFuncDefName(tree), closure);
}

Lexeme* getFuncDefParams(Lexeme* tree)
{
    return car(cdr(tree));
}

Lexeme* getFuncDefBody(Lexeme* tree)
{
    return cdr(cdr(tree));
}

Lexeme* getFuncDefName(Lexeme* tree)
{
    return car(tree);
}


// Functions for evaluation Function calls
Lexeme* evalFuncCall(Lexeme* tree, Lexeme* env)
{
    Lexeme* closure = eval(getFuncCallName(tree), env);
    Lexeme* args = getFuncCallArgs(tree);
    Lexeme* params = getClosureParams(closure);
    Lexeme* body = getClosureBody(closure);
    Lexeme* senv = getClosureEnvironment(closure);
    Lexeme* eargs = evalArgs(args, env);
    Lexeme* xenv = extend(senv, params, eargs);

    insertEnvironment(xenv, newLexemeWord(ID, THIS), xenv);

    return eval(body, xenv);
}

Lexeme* getFuncCallName(Lexeme* tree)
{
    return car(tree);
}

Lexeme* getFuncCallArgs(Lexeme* tree)
{
    return cdr(tree);
}

Lexeme* getClosureParams(Lexeme* closure)
{
    return car(cdr(closure));
}

Lexeme* getClosureBody(Lexeme* closure)
{
    return car(cdr(cdr(closure)));
}

Lexeme* getClosureEnvironment(Lexeme* closure)
{
    return car(closure);
}

Lexeme* evalArgs(Lexeme* args, Lexeme* env)
{
    Lexeme* iter = args;
    while (iter != NULL) {
        eval(car(iter), env);
        iter = cdr(iter);
    }
    return args;
}

Lexeme* evalPrint(Lexeme* tree, Lexeme* env)
{
    Lexeme* result = eval(cdr(tree), env);
    char* rtype = getLexemeType(result);

    if (strcmp(INTEGER, rtype) == 0) {
        printf("%d", getLexemeInt(result));
        return result;
    }

    else if (strcmp(STRING, rtype) == 0) {
        printf("\"%s\"", getLexemeString(result));
        return result;
    }

    else if (strcmp(BOOLEAN, rtype) == 0) {
        printf("\"%s\"", getLexemeString(result));
        return result;
    }
    else {
        printf("didn't get that!\n");
        return result;
    }
}

Lexeme* evalReturn(Lexeme* tree, Lexeme* env)
{
    return eval(cdr(tree), env);
}

Lexeme* evalBlock(Lexeme* tree, Lexeme* env)
{
    Lexeme* result;
    tree = cdr(tree); // I stored my blocks kinda weird
    while (tree != NULL) {
        result = eval(car(tree), env);
        if (strcmp(getLexemeType(result), RETURNED) == 0) {
            return result;
        }
        tree = cdr(tree);
    }
    return result;
}



// Functions for evaluating simple operations
Lexeme* evalPlus(Lexeme* tree, Lexeme* env)
{
    char* ltype = getLexemeType(car(tree));
    char* rtype = getLexemeType(cdr(tree));

    if (strcmp(ltype, rtype) != 0) { // Two lexemes were of wrong type
        return newLexemeError(ERROR, "Bad Operation Error", LINE);
    }

    else if (strcmp(ltype, INTEGER) == 0) {
        int a = getLexemeInt(car(tree)) + getLexemeInt(cdr(tree));
        char buffer[64];
        sprintf(buffer, "%d", a);
        return newLexemeWord(INTEGER, buffer);
    }

    else if (strcmp(ltype, STRING) == 0) {
        char* a = getLexemeString(car(tree));
        char* b = getLexemeString(cdr(tree));
        char* new = malloc(strlen(a) + strlen(b) + 1);
        strcpy(new, a);
        strcat(new, b);
        return newLexemeWord(STRING, new);
    }

    else if (strcmp(ltype, BOOLEAN) == 0) {
        if (strcmp(getLexemeString(car(tree)), "True") == 0) {
            // True + True/False == True
            return newLexemeWord(BOOLEAN, getLexemeString(car(tree)));
        }

        else {
            if (strcmp(getLexemeString(cdr(tree)), "True") == 0) {
            // True + True/False == True
                return newLexemeWord(BOOLEAN, getLexemeString(cdr(tree)));
            }
            else {
            // False + False = False
                return newLexemeWord(BOOLEAN, getLexemeString(car(tree)));
            }
        }
    }

    else { // Two lexemes were of wrong type
        return newLexemeError(ERROR, "Bad Operation Error", LINE);
    }
}

Lexeme* evalMinus(Lexeme* tree, Lexeme* env)
{
    char* ltype = getLexemeType(car(tree));
    char* rtype = getLexemeType(cdr(tree));

    if (strcmp(ltype, rtype) != 0) { // Two lexemes were of wrong type
        return newLexemeError(ERROR, "Bad Operation Error", LINE);
    }

    else if (strcmp(ltype, INTEGER) == 0) {
        int a = getLexemeInt(car(tree)) - getLexemeInt(cdr(tree));
        char buffer[64];
        sprintf(buffer, "%d", a);
        return newLexemeWord(INTEGER, buffer);
    }

    else { // Two lexemes were of wrong type
        return newLexemeError(ERROR, "Bad Operation Error", LINE);
    }
}

Lexeme* evalTimes(Lexeme* tree, Lexeme* env)
{
    char* ltype = getLexemeType(car(tree));
    char* rtype = getLexemeType(cdr(tree));

    if (strcmp(ltype, rtype) != 0) { // Two lexemes were of wrong type
        return newLexemeError(ERROR, "Bad Operation Error", LINE);
    }

    else if (strcmp(ltype, INTEGER) == 0) {
        int a = getLexemeInt(car(tree)) * getLexemeInt(cdr(tree));
        char buffer[64];
        sprintf(buffer, "%d", a);
        return newLexemeWord(INTEGER, buffer);
    }

    else { // Two lexemes were of wrong type
        return newLexemeError(ERROR, "Bad Operation Error", LINE);
    }
}

Lexeme* evalDivides(Lexeme* tree, Lexeme* env)
{
    char* ltype = getLexemeType(car(tree));
    char* rtype = getLexemeType(cdr(tree));

    if (strcmp(ltype, rtype) != 0) { // Two lexemes were of wrong type
        return newLexemeError(ERROR, "Bad Operation Error", LINE);
    }

    else if (strcmp(ltype, INTEGER) == 0) {
        int a = getLexemeInt(car(tree)) / getLexemeInt(cdr(tree));
        char buffer[64];
        sprintf(buffer, "%d", a);
        return newLexemeWord(INTEGER, buffer);
    }

    else { // Two lexemes were of wrong type
        return newLexemeError(ERROR, "Bad Operation Error", LINE);
    }
}

Lexeme* evalModulus(Lexeme* tree, Lexeme* env)
{
    char* ltype = getLexemeType(car(tree));
    char* rtype = getLexemeType(cdr(tree));

    if (strcmp(ltype, rtype) != 0) { // Two lexemes were of wrong type
        return newLexemeError(ERROR, "Bad Operation Error", LINE);
    }

    else if (strcmp(ltype, INTEGER) == 0) {
        int a = getLexemeInt(car(tree)) % getLexemeInt(cdr(tree));
        char buffer[64];
        sprintf(buffer, "%d", a);
        return newLexemeWord(INTEGER, buffer);
    }

    else { // Two lexemes were of wrong type
        return newLexemeError(ERROR, "Bad Operation Error", LINE);
    }
}

Lexeme* evalEquals(Lexeme* tree, Lexeme* env)
{
    char* ltype = getLexemeType(car(tree));
    char* rtype = getLexemeType(cdr(tree));
    char rval[6]; // Going to return a true or false lexeme

    if (strcmp(ltype, rtype) != 0) { // Two lexemes were of wrong type
        return newLexemeError(ERROR, "Bad Operation Error", LINE);
    }

    else if (strcmp(ltype, INTEGER) == 0) {
        if (getLexemeInt(car(tree)) == getLexemeInt(cdr(tree)))
            strcpy(rval, "True");
        else
            strcpy(rval, "False");

        return newLexemeWord(BOOLEAN, rval);
    }

    else if (strcmp(ltype, STRING) == 0) {
        char* a = getLexemeString(car(tree));
        char* b = getLexemeString(cdr(tree));
        if (strcmp(a, b) == 0)
            strcpy(rval, "True");

        else
            strcpy(rval, "False");

        return newLexemeWord(BOOLEAN, rval);
    }

    else if (strcmp(ltype, BOOLEAN) == 0) {
        char* a = getLexemeString(car(tree));
        char* b = getLexemeString(cdr(tree));
        if (strcmp(a, b) == 0)
            strcpy(rval, "True");

        else
            strcpy(rval, "False");

        return newLexemeWord(BOOLEAN, rval);
    }

    else { // Two lexemes were of wrong type
        return newLexemeError(ERROR, "Bad Operation Error", LINE);
    }
}

Lexeme* evalGreaterThan(Lexeme* tree, Lexeme* env)
{
    char* ltype = getLexemeType(car(tree));
    char* rtype = getLexemeType(cdr(tree));
    char rval[6];

    if (strcmp(ltype, rtype) != 0) { // Two lexemes were of wrong type
        return newLexemeError(ERROR, "Bad Operation Error", LINE);
    }

    else if (strcmp(ltype, INTEGER) == 0) {
        int a = getLexemeInt(car(tree));
        int b = getLexemeInt(cdr(tree));
        if (a > b)
            strcpy(rval, "True");
        else
            strcpy(rval, "False");

        return newLexemeWord(BOOLEAN, rval);
    }

    else { // Two lexemes were of wrong type
        return newLexemeError(ERROR, "Bad Operation Error", LINE);
    }
}

Lexeme* evalLessThan(Lexeme* tree, Lexeme* env)
{
    char* ltype = getLexemeType(car(tree));
    char* rtype = getLexemeType(cdr(tree));
    char rval[6];

    if (strcmp(ltype, rtype) != 0) { // Two lexemes were of wrong type
        return newLexemeError(ERROR, "Bad Operation Error", LINE);
    }

    else if (strcmp(ltype, INTEGER) == 0) {
        int a = getLexemeInt(car(tree));
        int b = getLexemeInt(cdr(tree));
        if (a < b)
            strcpy(rval, "True");
        else
            strcpy(rval, "False");

        return newLexemeWord(BOOLEAN, rval);
    }

    else { // Two lexemes were of wrong type
        return newLexemeError(ERROR, "Bad Operation Error", LINE);
    }
}

Lexeme* evalAssign(Lexeme* tree, Lexeme* env)
{
    Lexeme* val = eval(cdr(tree), env);

    if (strcmp(getLexemeType(car(tree)), AT) == 0) { // LHS is an object variable
        Lexeme* obj = eval(car(car(tree)), env);
        updateVal(obj, car(cdr(tree)), val);
    }
    else {
        updateVal(env, car(tree), val);
    }
    return val;
}

Lexeme* evalAnd(Lexeme* tree, Lexeme* env)
{
    if (strcmp(getLexemeString(car(tree)), "False") == 0) {
        // False AND True/False == False
        return newLexemeWord(BOOLEAN, getLexemeString(car(tree)));
    }

    else {
        if (strcmp(getLexemeString(cdr(tree)), "False") == 0) {
            // True AND False == False
            return newLexemeWord(BOOLEAN, getLexemeString(cdr(tree)));
        }
        else {
        // True AND True = True
            return newLexemeWord(BOOLEAN, getLexemeString(car(tree)));
        }
    }
}

Lexeme* evalOr(Lexeme* tree, Lexeme* env)
{
    if (strcmp(getLexemeString(car(tree)), "True") == 0) {
        // True OR True/False == True
        return newLexemeWord(BOOLEAN, getLexemeString(car(tree)));
    }

    else {
        if (strcmp(getLexemeString(cdr(tree)), "True") == 0) {
            // False OR True == True
            return newLexemeWord(BOOLEAN, getLexemeString(cdr(tree)));
        }
        else {
        // False OR False == False
            return newLexemeWord(BOOLEAN, getLexemeString(car(tree)));
        }
    }
}

Lexeme* evalNot(Lexeme* tree, Lexeme* env)
{
    Lexeme* result = eval(cdr(tree), env);
    char rval[6];
    if (strcmp(getLexemeString(result), "True") == 0) {
        strcpy(rval, "False");
        return newLexemeWord(BOOLEAN, rval);
    }
    else {
        strcpy(rval, "True");
        return newLexemeWord(BOOLEAN, rval);
    }
}

Lexeme* evalAt(Lexeme* tree, Lexeme* env)
{
    Lexeme* object = eval(car(tree), env); // LHS is object
    return eval(cdr(tree), object); // objects == environments :O
}

Lexeme* evalVarDef(Lexeme* tree, Lexeme* env)
{


}

Lexeme* evalIf(Lexeme* tree, Lexeme* env)
{


}

Lexeme* evalWhile(Lexeme* tree, Lexeme* env)
{


}
