
#include "lexeme.h"
#include "tree.h"
#include <stdio.h>

void printLevelOrder(Lexeme* tree)
{
    int h = height(tree);
    int i;
    for (i = 1; i < h; i++) {
        printf("%d\n", i);
        printGivenLevel(tree, i);
    }
}

void printGivenLevel(Lexeme* tree, int level)
{
    if (tree == NULL) {
        //printf("(null)");
        return;
    }
    if (level == 1) printf("(%s) ", getLexemeType(tree));
    else if (level > 1) {
        printGivenLevel(car(tree), level - 1);
        printGivenLevel(cdr(tree), level - 1);
    }
}

int height(Lexeme* tree)
{
    if (tree == NULL) return 0;
    else {
        int lheight = height(car(tree));
        int rheight = height(cdr(tree));
        if (lheight > rheight)
            return lheight+1;
        else
            return rheight+1;
    }
}
