/* Program written by Alex Johnson
/  2/10/2019 - CS 403 - Dr. Lusth
/  To use, run "environement".
*/

#include "types.h"
#include "lexeme.h"
#include "environment.h"
#include "parser.h"
#include "eval.h"
#include "tree.h"

#include <stdio.h>

FILE* fp; // Need a global file pointer

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("Use is ./johnsonscript file.johns [optArgs]\n");
        return -1;
    }
    countCL = argc;
    argsCL = argv;

    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("Couldn't open file %s\n", argv[1]);
        return -1;
    }

    Lexeme* tree = parse();
    Lexeme* env = newEnvironment();
    //printLevelOrder(tree);

    eval(tree, env);
    return 0;
}
