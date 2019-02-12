/* Program written by Alex Johnson
/  2/10/2019 - CS 403 - Dr. Lusth
/  environment.c contains functions for creating environments for the programming language.
*/

#include "lexeme.h"
#include "types.h"
#include "environment.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int envDemo()
{
    Lexeme* env;
    Lexeme* var;
    Lexeme* val;

    Lexeme* vars;
    Lexeme* vals;

    Lexeme* find;


    printf("Creating a new environment\n");
    env = newEnvironment();
    displayEnvironment(env, 0);

    printf("\nAdding variable x with value 3\n");
    var = newLexemeWord(ID, "x");
    val = newLexemeWord(INTEGER, "3");
    insertEnvironment(env, var, val);

    displayEnvironment(env, 0);

    printf("\nExtending the environment with y: 4 and z: \"hello\"\n");

    vars = cons(TABLE, newLexemeWord(ID, "y"), NULL);
    vals = cons(TABLE, newLexemeWord(INTEGER, "4"), NULL);
    env = extend(env, vars, vals);

    var = newLexemeWord(ID, "z");
    val = newLexemeWord(STRING, "hello");
    insertEnvironment(env, var, val);

    displayEnvironment(env, 0);

    printf("\nUpdating the variable y to be equal to 7\n");
    var = newLexemeWord(ID, "y");
    val = newLexemeWord(INTEGER, "7");

    updateVal(env, var, val);

    displayEnvironment(env, 0);

    printf("\nDisplaying just the local environment\n");
    displayEnvironment(env, 1);

    printf("\nSearching for the value x\n");
    var = newLexemeWord(ID, "x");
    find = getVal(env, var);
    printf("x is ");
    displayLexeme(find);
    printf("\n");

    printf("\nSearching for the value w\n");
    var = newLexemeWord(ID, "w");
    find = getVal(env, var);
    printf("w is ");
    displayLexeme(find);
    printf("\n");

    return 0;
}

Lexeme* newEnvironment()
{
    return cons(ENV, cons(TABLE, NULL, NULL), NULL);
}

Lexeme* insertEnvironment(Lexeme* env, Lexeme* id, Lexeme* val)
{
    setCar(car(env), cons(ID, id, car(car(env))));
    setCdr(car(env), cons(getLexemeType(val), val, cdr(car(env))));

    return val;
}

Lexeme* getVal(Lexeme* env, Lexeme* id)
{
    while (env != NULL) {
        Lexeme* vars = car(car(env));
        Lexeme* vals = cdr(car(env));

        while (vars != NULL) {
            if (strcmp(getLexemeString(id), getLexemeString(car(vars))) == 0)
                // We found the correct variable
                return car(vals);
            vars = cdr(vars);
            vals = cdr(vals);
        }
        env = cdr(env);
    }
    Lexeme* new = newLexemeError(ERROR, "Undefined Variable Error", 0);
    return new;
    //displayLexeme(new);
}

Lexeme* updateVal(Lexeme* env, Lexeme* id, Lexeme* val)
{
    while (env != NULL) {
        Lexeme* vars = car(car(env));
        Lexeme* vals = cdr(car(env));

        while (vars != NULL) {
            if (strcmp(getLexemeString(id), getLexemeString(car(vars))) == 0) {
                // We found the correct variable
                //TODO fix update func
                setCar(vals, val);
                return car(vals);
            }
            vars = cdr(vars);
            vals = cdr(vals);
        }
        env = cdr(env);
    }
    Lexeme* new = newLexemeError(ERROR, "Undefined Variable Error", 0);
    return new;
    //displayLexeme(new);
    //exit(-1);
}

Lexeme* extend(Lexeme* env, Lexeme* ids, Lexeme* vals)
{
    return cons(ENV, cons(TABLE, ids, vals), env);
}

void displayEnvironment(Lexeme* env, int local)
{
    int flag = 0;
    if (cdr(env) != NULL) {
        printf("The local environment is: \n");
        flag = 1;
    }
    else {
        printf("The environment is: \n");
    }

    while (env != NULL) {
        Lexeme* vars = car(car(env));
        Lexeme* vals = cdr(car(env));

        while (vars != NULL) {
            displayLexeme(car(vars));
            printf(" -> ");
            displayLexeme(car(vals));
            printf("\n");
            vars = cdr(vars);
            vals = cdr(vals);
        }
        env = cdr(env);

        if (local) break;
        if (flag) {
            printf("The environment is: \n");
            flag = 0;
        }
    }
}
