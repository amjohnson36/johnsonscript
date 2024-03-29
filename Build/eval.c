

#include "eval.h"
#include "lexeme.h"
#include "types.h"
#include "environment.h"
#include "lex.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int countCL;
char** argsCL;

Lexeme* eval(Lexeme* tree, Lexeme* env)
{

    if (tree == NULL) return NULL;

    //printf("\nlexeme: ");displayLexeme(tree); printf("\n");
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

    else if (strcmp(type, FILEPOINTER) == 0) {
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

    else if (strcmp(type, NEGATIVE) == 0) {
        return evalNegative(tree, env);
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

    else if (strcmp(type, PRINT) == 0) {
        return evalPrint(tree, env);
    }

    else if (strcmp(type, NEWARRAY) == 0) {
        return evalNewArray(tree, env);
    }

    else if (strcmp(type, GETARRAY) == 0) {
        return evalGetArray(tree, env);
    }

    else if (strcmp(type, SETARRAY) == 0) {
        return evalSetArray(tree, env);
    }

    else if (strcmp(type, GETARGCOUNT) == 0) {
        return evalGetArgCount();
    }

    else if (strcmp(type, GETARG) == 0) {
        return evalGetArg(tree, env);
    }

    else if (strcmp(type, OPENFILE) == 0) {
        return evalOpenFile(tree, env);
    }

    else if (strcmp(type, READINTEGER) == 0) {
        return evalReadInteger(tree, env);
    }

    else if (strcmp(type, ATFILEEND) == 0) {
        return evalAtFileEnd(tree, env);
    }

    else if (strcmp(type, CLOSEFILE) == 0) {
        return evalCloseFile(tree, env);
    }

    else if (strcmp(type, LAMBDA) == 0) {
        return evalLambda(tree, env);
    }

    else if (strcmp(type, BLOCK) == 0) {
        return evalBlock(tree, env);
    }

    else if (strcmp(type, OPAREN) == 0) {
        return eval(cdr(tree), env);
    }

    else if (strcmp(type, PROGRAM) == 0) {
        Lexeme* result;
        while (tree != NULL) {
            result = eval(car(tree), env);
            tree = cdr(tree);
        }
        return result;
    }

    else if (strcmp(type, ERROR) == 0) {
        printf("\nIllegal\n");
        displayLexeme(tree);
        printf("\n");
        exit(-1);
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

Lexeme* evalLambda(Lexeme* tree, Lexeme* env)
{
    //return cons(CLOSURE, env, tree);
    return cons(CLOSURE, env,
            cons(JOIN, getFuncDefParams(tree),
             cons(JOIN, getFuncDefBody(tree), NULL)));
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

    // insert a variable that points to xenv
    insertEnvironment(xenv, newLexemeWord(ID, "this"), xenv);

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
    if (args == NULL)
        return NULL;

    return cons(JOIN, eval(car(args), env), evalArgs(cdr(args), env));
}

Lexeme* evalPrint(Lexeme* tree, Lexeme* env)
{
    Lexeme* result = eval(cdr(tree), env);
    char* rtype = getLexemeType(result);

    if (result == NULL) {
        printf("NULL");
        return NULL;
    }

    else if (strcmp(INTEGER, rtype) == 0) {
        printf("%d", getLexemeInt(result));
        return result;
    }

    else if (strcmp(STRING, rtype) == 0) {
        printf("%s", getLexemeString(result));
        return result;
    }

    else if (strcmp(BOOLEAN, rtype) == 0) {
        printf("%s", getLexemeString(result));
        return result;
    }
    else {
        printf("I didn't get that!");
        return result;
    }
}

Lexeme* evalNewArray(Lexeme* tree, Lexeme* env)
{
    Lexeme* eargs = evalArgs(cdr(tree), env);
    checkArgsLength(eargs, 1);

    Lexeme* size = car(eargs);
    if (strcmp(getLexemeType(size), INTEGER) != 0) {
        // Arg was not an integer
        Lexeme* a = newLexemeError(ERROR, "Invalid Arguments Error", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }

    Lexeme* array = newLexemeArray(ARRAY, getLexemeInt(size));
    return array;
}

Lexeme* evalGetArray(Lexeme* tree, Lexeme* env)
{
    Lexeme* eargs = evalArgs(cdr(tree), env);
    checkArgsLength(eargs, 2);

    Lexeme* array = car(eargs);
    Lexeme* size = car(cdr(eargs));
    if ((strcmp(getLexemeType(array), ARRAY) != 0) ||
            (strcmp(getLexemeType(size), INTEGER) != 0)) {
        // Arg was not an integer
        Lexeme* a = newLexemeError(ERROR, "Invalid Arguments Error", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }

    return getLexemeArray(array, getLexemeInt(size));
}

Lexeme* evalSetArray(Lexeme* tree, Lexeme* env)
{
    Lexeme* eargs = evalArgs(cdr(tree), env);
    checkArgsLength(eargs, 3);

    Lexeme* array = car(eargs);
    Lexeme* size = car(cdr(eargs));
    Lexeme* val = car(cdr(cdr(eargs)));
    if ((strcmp(getLexemeType(array), ARRAY) != 0) ||
            (strcmp(getLexemeType(size), INTEGER) != 0)) {
        // Arg was not an array or integer
        Lexeme* a = newLexemeError(ERROR, "Invalid Arguments Error", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }
    setLexemeArray(array, size, val);
    return val;
}

int argsLength(Lexeme* tree)
{
    int count = 0;
    while (tree != NULL) {
        count++;
        tree = cdr(tree);
    }
    return count;
}

void checkArgsLength(Lexeme* eargs, int num)
{
    if (argsLength(eargs) != num) {
        // Incorrect number of args, throw error
        Lexeme* a = newLexemeError(ERROR, "Invalid Arguments Error", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }
}

Lexeme* evalGetArgCount()
{
    char buffer[64];
    sprintf(buffer, "%d", countCL);
    return newLexemeWord(INTEGER, buffer);
}

Lexeme* evalGetArg(Lexeme* tree, Lexeme* env)
{
    Lexeme* eargs = evalArgs(cdr(tree), env);
    checkArgsLength(eargs, 1);

    Lexeme* index = car(eargs);
    return newLexemeWord(STRING, argsCL[getLexemeInt(index)]);
}

Lexeme* evalOpenFile(Lexeme* tree, Lexeme* env)
{

    Lexeme* eargs = evalArgs(cdr(tree), env);
    checkArgsLength(eargs, 1);

    Lexeme* fname = car(eargs);
    Lexeme* f = newLexemeFP(FILEPOINTER, fname);
    return f;
}

Lexeme* evalReadInteger(Lexeme* tree, Lexeme* env)
{
    Lexeme* eargs = evalArgs(cdr(tree), env);
    checkArgsLength(eargs, 1);

    FILE* f = getLexemeFP(car(eargs));
    int a;
    fscanf(f, "%d", &a);
    char buffer[64];
    sprintf(buffer, "%d", a);
    return newLexemeWord(INTEGER, buffer);
}

Lexeme* evalAtFileEnd(Lexeme* tree, Lexeme* env)
{
    Lexeme* eargs = evalArgs(cdr(tree), env);
    checkArgsLength(eargs, 1);

    FILE* f = getLexemeFP(car(eargs));
    if (feof(f)) return newLexemeWord(BOOLEAN, "True");
    else return newLexemeWord(BOOLEAN, "False");
}

Lexeme* evalCloseFile(Lexeme* tree, Lexeme* env)
{
    Lexeme* eargs = evalArgs(cdr(tree), env);
    checkArgsLength(eargs, 1);

    FILE* f = getLexemeFP(car(eargs));
    fclose(f);
    return newLexemeWord(BOOLEAN, "True");
}

Lexeme* evalBlock(Lexeme* tree, Lexeme* env)
{
    Lexeme* result;
    tree = cdr(tree); // I stored my blocks kinda weird
    while (tree != NULL) {
        result = eval(car(tree), env);
        tree = cdr(tree);
    }
    return result;
}

// Functions for evaluating simple operations
Lexeme* evalPlus(Lexeme* tree, Lexeme* env)
{
    Lexeme* left = eval(car(tree), env);
    Lexeme* right = eval(cdr(tree), env);
    char* ltype = getLexemeType(left);
    char* rtype = getLexemeType(right);

    if (((strcmp(ltype, INTEGER) == 0) && (strcmp(rtype, STRING) == 0)) ||
            ((strcmp(ltype, STRING) == 0) && (strcmp(rtype, INTEGER) == 0))) {
                // One of the values is a string, the other is a integer
                if (strcmp(ltype, INTEGER) == 0) {
                    int a = getLexemeInt(left);
                    char* b = getLexemeString(right);
                    char buffer[strlen(b) + 65];
                    sprintf(buffer, "%d%s", a, b);
                    return newLexemeWord(STRING, buffer);
                }
                if (strcmp(rtype, INTEGER) == 0) {
                    char* a = getLexemeString(left);
                    int b = getLexemeInt(right);
                    char buffer[strlen(a) + 65];
                    sprintf(buffer, "%s%d", a, b);
                    return newLexemeWord(STRING, buffer);
                }
            }

    else if (strcmp(ltype, rtype) != 0) { // Two lexemes were of wrong type
        Lexeme* a = newLexemeError(ERROR, "Bad Operation Error: +", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }

    else if (strcmp(ltype, INTEGER) == 0) {
        int a = getLexemeInt(left) + getLexemeInt(right);
        char buffer[64];
        sprintf(buffer, "%d", a);
        return newLexemeWord(INTEGER, buffer);
    }

    else if (strcmp(ltype, STRING) == 0) {
        char* a = getLexemeString(left);
        char* b = getLexemeString(right);
        char* new = malloc(strlen(a) + strlen(b) + 1);
        strcpy(new, a);
        strcat(new, b);
        return newLexemeWord(STRING, new);
    }

    else if (strcmp(ltype, BOOLEAN) == 0) {
        if (strcmp(getLexemeString(left), "True") == 0) {
            // True + True/False == True
            return newLexemeWord(BOOLEAN, getLexemeString(car(tree)));
        }

        else {
            if (strcmp(getLexemeString(right), "True") == 0) {
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
        Lexeme* a = newLexemeError(ERROR, "Bad Operation Error: +", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }
    return NULL;
}

Lexeme* evalMinus(Lexeme* tree, Lexeme* env)
{
    Lexeme* left = eval(car(tree), env);
    Lexeme* right = eval(cdr(tree), env);
    char* ltype = getLexemeType(left);
    char* rtype = getLexemeType(right);

    if (strcmp(ltype, rtype) != 0) { // Two lexemes were of wrong type
        Lexeme* a = newLexemeError(ERROR, "Bad Operation Error: -", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }

    else if (strcmp(ltype, INTEGER) == 0) {
        int a = getLexemeInt(left) - getLexemeInt(right);
        char buffer[64];
        sprintf(buffer, "%d", a);
        return newLexemeWord(INTEGER, buffer);
    }

    else { // Two lexemes were of wrong type
        Lexeme* a = newLexemeError(ERROR, "Bad Operation Error: -", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }
}

Lexeme* evalTimes(Lexeme* tree, Lexeme* env)
{
    Lexeme* left = eval(car(tree), env);
    Lexeme* right = eval(cdr(tree), env);
    char* ltype = getLexemeType(left);
    char* rtype = getLexemeType(right);

    if (strcmp(ltype, rtype) != 0) { // Two lexemes were of wrong type
        Lexeme* a = newLexemeError(ERROR, "Bad Operation Error: *", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }

    else if (strcmp(ltype, INTEGER) == 0) {
        int a = getLexemeInt(left) * getLexemeInt(right);
        char buffer[64];
        sprintf(buffer, "%d", a);
        return newLexemeWord(INTEGER, buffer);
    }

    else { // Two lexemes were of wrong type
        Lexeme* a = newLexemeError(ERROR, "Bad Operation Error: *", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }
}

Lexeme* evalDivides(Lexeme* tree, Lexeme* env)
{
    Lexeme* left = eval(car(tree), env);
    Lexeme* right = eval(cdr(tree), env);
    char* ltype = getLexemeType(left);
    char* rtype = getLexemeType(right);

    if (strcmp(ltype, rtype) != 0) { // Two lexemes were of wrong type
        Lexeme* a = newLexemeError(ERROR, "Bad Operation Error: /", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }

    else if (strcmp(ltype, INTEGER) == 0) {
        int a = getLexemeInt(left) / getLexemeInt(cdr(tree));
        char buffer[64];
        sprintf(buffer, "%d", a);
        return newLexemeWord(INTEGER, buffer);
    }

    else { // Two lexemes were of wrong type
        Lexeme* a = newLexemeError(ERROR, "Bad Operation Error: /", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }
}

Lexeme* evalModulus(Lexeme* tree, Lexeme* env)
{
    Lexeme* left = eval(car(tree), env);
    Lexeme* right = eval(cdr(tree), env);
    char* ltype = getLexemeType(left);
    char* rtype = getLexemeType(right);

    if (strcmp(ltype, rtype) != 0) { // Two lexemes were of wrong type
        Lexeme* a = newLexemeError(ERROR, "Bad Operation Error: %", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }

    else if (strcmp(ltype, INTEGER) == 0) {
        int a = getLexemeInt(left) % getLexemeInt(right);
        char buffer[64];
        sprintf(buffer, "%d", a);
        return newLexemeWord(INTEGER, buffer);
    }

    else { // Two lexemes were of wrong type
        Lexeme* a = newLexemeError(ERROR, "Bad Operation Error: %", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }
}

Lexeme* evalEquals(Lexeme* tree, Lexeme* env)
{
    Lexeme* left = eval(car(tree), env);
    Lexeme* right = eval(cdr(tree), env);
    char* ltype = getLexemeType(left);
    char* rtype = getLexemeType(right);
    char rval[6]; // Going to return a true or false lexeme

    if (strcmp(ltype, rtype) != 0) { // Two lexemes were of wrong type
        strcpy(rval, "False");
        return newLexemeWord(BOOLEAN, rval);
    }

    else if (strcmp(ltype, INTEGER) == 0) {
        if (getLexemeInt(left) == getLexemeInt(right))
            strcpy(rval, "True");

        else
            strcpy(rval, "False");

        return newLexemeWord(BOOLEAN, rval);
    }

    else if (strcmp(ltype, STRING) == 0) {
        char* a = getLexemeString(left);
        char* b = getLexemeString(right);
        if (strcmp(a, b) == 0)
            strcpy(rval, "True");

        else
            strcpy(rval, "False");

        return newLexemeWord(BOOLEAN, rval);
    }

    else if (strcmp(ltype, BOOLEAN) == 0) {
        char* a = getLexemeString(left);
        char* b = getLexemeString(right);
        if (strcmp(a, b) == 0)
            strcpy(rval, "True");

        else
            strcpy(rval, "False");

        return newLexemeWord(BOOLEAN, rval);
    }

    else { // Two lexemes were of wrong type
        Lexeme* a = newLexemeError(ERROR, "Bad Operation Error: ==", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }
}

Lexeme* evalGreaterThan(Lexeme* tree, Lexeme* env)
{
    Lexeme* left = eval(car(tree), env);
    Lexeme* right = eval(cdr(tree), env);
    char* ltype = getLexemeType(left);
    char* rtype = getLexemeType(right);
    char rval[6];

    if (strcmp(ltype, rtype) != 0) { // Two lexemes were of wrong type
        Lexeme* a = newLexemeError(ERROR, "Bad Operation Error: >", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }

    else if (strcmp(ltype, INTEGER) == 0) {
        int a = getLexemeInt(left);
        int b = getLexemeInt(right);
        if (a > b)
            strcpy(rval, "True");
        else
            strcpy(rval, "False");

        return newLexemeWord(BOOLEAN, rval);
    }

    else { // Two lexemes were of wrong type
        Lexeme* a = newLexemeError(ERROR, "Bad Operation Error: >", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }
}

Lexeme* evalLessThan(Lexeme* tree, Lexeme* env)
{
    Lexeme* left = eval(car(tree), env);
    Lexeme* right = eval(cdr(tree), env);
    char* ltype = getLexemeType(left);
    char* rtype = getLexemeType(right);
    char rval[6];

    if (strcmp(ltype, rtype) != 0) { // Two lexemes were of wrong type
        Lexeme* a = newLexemeError(ERROR, "Bad Operation Error: <", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }

    else if (strcmp(ltype, INTEGER) == 0) {
        int a = getLexemeInt(left);
        int b = getLexemeInt(right);
        if (a < b)
            strcpy(rval, "True");
        else
            strcpy(rval, "False");

        return newLexemeWord(BOOLEAN, rval);
    }

    else { // Two lexemes were of wrong type
        Lexeme* a = newLexemeError(ERROR, "Bad Operation Error: <", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }
}

Lexeme* evalAssign(Lexeme* tree, Lexeme* env)
{
    Lexeme* val = eval(cdr(tree), env);
    if (strcmp(getLexemeType(car(tree)), AT) == 0) { // LHS is an object variable
        Lexeme* obj = eval(car(car(tree)), env);
        updateVal(obj, cdr(car(tree)), val);
    }
    else {
        updateVal(env, car(tree), val);
    }
    return val;
}

Lexeme* evalAnd(Lexeme* tree, Lexeme* env)
{
    Lexeme* left = eval(car(tree), env);
    Lexeme* right = eval(cdr(tree), env);
    char* ltype = getLexemeType(left);
    char* rtype = getLexemeType(right);

    if ((strcmp(ltype, rtype) != 0) || (strcmp(ltype, BOOLEAN) != 0)) {
        Lexeme* a = newLexemeError(ERROR, "Bad Operation Error: AND", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }

    if (strcmp(getLexemeString(left), "False") == 0) {
        // False AND True/False == False
        return newLexemeWord(BOOLEAN, getLexemeString(left));
    }

    else {
        if (strcmp(getLexemeString(right), "False") == 0) {
            // True AND False == False
            return newLexemeWord(BOOLEAN, getLexemeString(right));
        }
        else {
        // True AND True = True
            return newLexemeWord(BOOLEAN, getLexemeString(left));
        }
    }
}

Lexeme* evalOr(Lexeme* tree, Lexeme* env)
{
    Lexeme* left = eval(car(tree), env);
    Lexeme* right = eval(cdr(tree), env);
    char* ltype = getLexemeType(left);
    char* rtype = getLexemeType(right);

    if ((strcmp(ltype, rtype) != 0) || (strcmp(ltype, BOOLEAN) != 0)) {
        Lexeme* a = newLexemeError(ERROR, "Bad Operation Error: OR", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }
    if (strcmp(getLexemeString(left), "True") == 0) {
        // True OR True/False == True
        return newLexemeWord(BOOLEAN, getLexemeString(left));
    }

    else {
        if (strcmp(getLexemeString(right), "True") == 0) {
            // False OR True == True
            return newLexemeWord(BOOLEAN, getLexemeString(right));
        }
        else {
        // False OR False == False
            return newLexemeWord(BOOLEAN, getLexemeString(left));
        }
    }
}

Lexeme* evalNot(Lexeme* tree, Lexeme* env)
{
    Lexeme* result = eval(cdr(cdr(tree)), env); //not -> oparen -> expression
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

Lexeme* evalNegative(Lexeme* tree, Lexeme* env)
{
    Lexeme* result = eval(cdr(tree), env);
    if (strcmp(getLexemeType(result), INTEGER) != 0) {
        Lexeme* a = newLexemeError(ERROR, "Bad Operation Error: NEG", -1);
        printf("\nIllegal\n");
        displayLexeme(a);
        printf("\n");
        exit(-1);
    }
    int a = getLexemeInt(result);
    char buffer[64];
    sprintf(buffer, "%d", a * -1);
    return newLexemeWord(INTEGER, buffer);
}

Lexeme* evalAt(Lexeme* tree, Lexeme* env)
{
    // LHS must eval to object, RHS to variable
    Lexeme* object = eval(car(tree), env); // LHS is object
    return eval(cdr(tree), object); // objects == environments :O
}

Lexeme* evalVarDef(Lexeme* tree, Lexeme* env)
{
    if (cdr(tree) == NULL) { // defined like var x.
        return insertEnvironment(env, car(tree), NULL);
    }
    else {
        Lexeme* result = eval(cdr(cdr(tree)), env);
        return insertEnvironment(env, car(tree), result);
    }
}

Lexeme* evalIf(Lexeme* tree, Lexeme* env)
{
    Lexeme* condition = eval(car(tree), env);
    if (strcmp(getLexemeString(condition), "True") == 0 ||
        (getLexemeInt(condition) != 0)) { // If statement evaluated to True
            return eval(car(cdr(tree)), env);
        }
    else { // Condition evaluated to false, run else block
        if (cdr(cdr(tree)) != NULL)
            return eval(cdr(cdr(tree)), env);
    }
    return NULL;
}

Lexeme* evalWhile(Lexeme* tree, Lexeme* env)
{
    Lexeme* condition = eval(car(tree), env);
    Lexeme* result;
    while (strcmp(getLexemeString(condition), "True") == 0 ||
        (getLexemeInt(condition) != 0)) { // While statement evaluated to True
            result = eval(cdr(tree), env);
            condition = eval(car(tree), env);
        }
    return result;
}
