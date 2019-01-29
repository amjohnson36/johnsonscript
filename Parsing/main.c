/* Program written by Alex Johnson
/  1/25/2019 - CS 403 - Dr. Lusth
/  To use, run "recognizer <f>" where <f> is the name of the file to be scanned.
*/

#include "types.h"
#include "lexeme.h"
#include "lex.h"
#include "parser.h"

#include <stdio.h>
FILE* fp;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Use is ./recognizer filename\n");
        return -1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Couldn't open file %s\n", argv[1]);
        return -1;
    }
    
    return parse(fp);
}
