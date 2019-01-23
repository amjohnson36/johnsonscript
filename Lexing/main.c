#include "types.h"
#include "lexeme.h"
#include "scanner.h"
#include "lex.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Use is ./scanner filename\n");
        return -1;
    }
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Couldn't open file %s\n", argv[1]);
        return -1;
    }

    scanner(fp);
    return 0;
}
