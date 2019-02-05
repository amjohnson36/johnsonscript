#include "lexeme.h"
#include "types.h"
#include "environment.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int envDemo()
{
    printf("Creating a new environment\n");
    Lexeme* env = newEnvironment();
    displayEnvironment(env);

    printf("\nAdding variable x with value 3\n");
    Lexeme* var = newLexemeWord(ID, "x");
    Lexeme* val = newLexemeWord(INTEGER, "3");
    insertEnvironment(env, var, val);

    displayEnvironment(env);

    printf("\nExtending the environment with y: 4 and z: \"hello\"\n");


    env = extend(env, car(car(env)), cdr(car(env)));

    var = newLexemeWord(ID, "y");
    val = newLexemeWord(INTEGER, "4");
    insertEnvironment(env, var, val);

    var = newLexemeWord(ID, "z");
    val = newLexemeWord(STRING, "hello");
    insertEnvironment(env, var, val);
    

    displayEnvironment(env);


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
    displayLexeme(new);
    exit(-1);
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
    displayLexeme(new);
    exit(-1);
}

Lexeme* extend(Lexeme* env, Lexeme* ids, Lexeme* vals)
{
    return cons(ENV, cons(TABLE, ids, vals), env);
}

void displayEnvironment(Lexeme* env)
{
    printf("The environment is: \n");
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
    }
}
