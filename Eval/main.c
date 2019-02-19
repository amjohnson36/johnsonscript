/* Program written by Alex Johnson
/  2/10/2019 - CS 403 - Dr. Lusth
/  To use, run "environement".
*/

#include "types.h"
#include "lexeme.h"
#include "environment.h"
#include "parser.h"
#include "eval.h"

#include <stdio.h>

FILE* fp; // Need a global file pointer

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Use is ./johnsonscript file.johns");
        return -1;
    }
    fp = fopen(argv[1], "r");

    Lexeme* tree = parse();
    Lexeme* env = newEnvironment();
    eval(tree, env);
    
    return 0;
}
