/* Program written by Alex Johnson
/  2/01/2019 - CS 403 - Dr. Lusth
/  To use, run "recognizer <f>" where <f> is the name of the file to be scanned.
*/

#include "types.h"
#include "lexeme.h"
#include "lex.h"
#include "environment.h"

#include <stdio.h>

FILE* fp; // Need a global file pointer

int main(void)
{
    return envDemo();
}
