/* Program written by Alex Johnson
/  1/25/2019 - CS 403 - Dr. Lusth
/  lex.c contains functions for recognizing the various lexemes in the
/  source code and returning a lexeme object of that type.
*/

#include "types.h"
#include "lexeme.h"
#include "lex.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int LINE = 1;

Lexeme* lex(FILE* fp)
{
    int ch;
    skipWhiteSpace(fp);

    ch = getc(fp);
    if (ch == EOF) return newLexemeChar(END_OF_INPUT);

    switch(ch) {
        // single character tokens

        case '(': return newLexemeChar(OPAREN);
        case ')': return newLexemeChar(CPAREN);
        case ',': return newLexemeChar(COMMA);
        case '+': return newLexemeChar(PLUS);
        case '-': return newLexemeChar(MINUS);
        case '*': return newLexemeChar(TIMES);
        case '/': return newLexemeChar(DIVIDES);
        case '%': return newLexemeChar(MODULUS);
        case '>': return newLexemeChar(GREATERTHAN);
        case '<': return newLexemeChar(LESSTHAN);
        case '.': return newLexemeChar(DOT);
        case '#': return newLexemeChar(HASH);
        case '[': return newLexemeChar(OBRACKET);
        case ']': return newLexemeChar(CBRACKET);
        case '@': return newLexemeChar(AT);
        // TODO add other single characters

        default:
            if (ch == '=') { // Check whether it is '=' or '=='
                int ch2 = getc(fp);
                if (ch2 == '=') return newLexemeWord(EQUALS, "==");
                else {
                    ungetc(ch2, fp);
                    return newLexemeChar(ASSIGN);
                }
            }
            if (ch == '\\') { // Check whether it is '=' or '=='
                int ch2 = getc(fp);
                if (ch2 == 'n') return newLexemeWord(STRING, "\n");
                else {
                    ungetc(ch2, fp);
                }
            }
            if (isdigit(ch)) { // Get Integer
                ungetc(ch, fp);
                return lexNumber(fp);
            }
            else if (isalpha(ch)) { // Check whether variable or keyword
                ungetc(ch, fp);
                return lexVariableOrKeyword(fp);
            }
            else if (ch == '\"') { // Must be opening of string
                return lexString(fp);
            }
            else {
                return newLexemeError(ERROR, "Unknown Character Error", LINE);
            }
    }
}

Lexeme* lexNumber(FILE* fp)
{
    int ch;
    char buffer[64] = "";
    int count = 0;

    ch = getc(fp);
    while ((ch != EOF) && (isdigit(ch))) {
        count++;
        if (count > 63) {
            return newLexemeError(ERROR, "Buffer Overflow Error", LINE);
        }

        buffer[strlen(buffer)] = ch;
        ch = getc(fp);
    }

    ungetc(ch, fp);

    return newLexemeWord(INTEGER, buffer);
}

Lexeme* lexVariableOrKeyword(FILE* fp)
{
    int ch;
    char buffer[64] = "";
    unsigned int count = 0;

    ch = getc(fp);
    while (isalnum(ch)) {
        count++;
        if (count > sizeof(buffer) - 2) {
            return newLexemeError(ERROR, "Buffer Overflow Error", LINE);
        }

        buffer[count-1] = ch;
        ch = getc(fp);
    }
    ungetc(ch, fp);
    buffer[count] = '\0';

    if (strcmp(buffer, "if") == 0) {
        return newLexemeWord(IF, buffer);
    }
    else if (strcmp(buffer, "else") == 0) {
        return newLexemeWord(ELSE, buffer);
    }
    else if (strcmp(buffer, "while") == 0) {
        return newLexemeWord(WHILE, buffer);
    }
    else if (strcmp(buffer, "print") == 0) {
        return newLexemeWord(PRINT, buffer);
    }
    else if (strcmp(buffer, "newarray") == 0) {
        return newLexemeWord(NEWARRAY, buffer);
    }
    else if (strcmp(buffer, "getarray") == 0) {
        return newLexemeWord(GETARRAY, buffer);
    }
    else if (strcmp(buffer, "setarray") == 0) {
        return newLexemeWord(SETARRAY, buffer);
    }
    else if (strcmp(buffer, "getargcount") == 0) {
        return newLexemeWord(GETARGCOUNT, buffer);
    }
    else if (strcmp(buffer, "getarg") == 0) {
        return newLexemeWord(GETARG, buffer);
    }
    else if (strcmp(buffer, "openfile") == 0) {
        return newLexemeWord(OPENFILE, buffer);
    }
    else if (strcmp(buffer, "readinteger") == 0) {
        return newLexemeWord(READINTEGER, buffer);
    }
    else if (strcmp(buffer, "atfileend") == 0) {
        return newLexemeWord(ATFILEEND, buffer);
    }
    else if (strcmp(buffer, "closefile") == 0) {
        return newLexemeWord(CLOSEFILE, buffer);
    }
    else if (strcmp(buffer, "var") == 0) {
        return newLexemeWord(VAR, buffer);
    }
    else if (strcmp(buffer, "def") == 0) {
        return newLexemeWord(DEF, buffer);
    }
    else if (strcmp(buffer, "start") == 0) {
        return newLexemeWord(START, buffer);
    }
    else if (strcmp(buffer, "stop") == 0) {
        return newLexemeWord(STOP, buffer);
    }
    else if (strcmp(buffer, "and") == 0) {
        return newLexemeWord(AND, buffer);
    }
    else if (strcmp(buffer, "or") == 0) {
        return newLexemeWord(OR, buffer);
    }
    else if (strcmp(buffer, "not") == 0) {
        return newLexemeWord(NOT, buffer);
    }
    else if ((strcmp(buffer, "True") == 0) || strcmp(buffer, "False") == 0) {
        return newLexemeWord(BOOLEAN, buffer);
    }
    else if (strcmp(buffer, "neg") == 0) {
        return newLexemeWord(NEGATIVE, buffer);
    }
    else if (strcmp(buffer, "lambda") == 0) {
        return newLexemeWord(LAMBDA, buffer);
    }
    else { //string is a variable
        return newLexemeWord(ID, buffer);
    }

}

Lexeme* lexString(FILE* fp)
{
    int ch;
    int length = 32;
    char* buffer = malloc(sizeof(char) * length + 1); // +1 for null byte
    int index = 0;

    ch = getc(fp);
    while ((ch != EOF) && (ch != '"')) {
        if (index == length) {
            buffer = realloc(buffer, sizeof(char) * length * 2 + 1);
            length *= 2;
        }

        buffer[index++] = ch;
        buffer[index] = '\0';
        ch = getc(fp);
    }
    if (ch == EOF) return newLexemeError(ERROR, "Bad String Error", LINE);
    return newLexemeWord(STRING, buffer);
}

void skipWhiteSpace(FILE* fp)
{
    int ch;
    ch = getc(fp);
    if (ch == '\n') LINE++;

    while (isspace(ch) || ch == '#') {
        if (ch == '#') { // Start of a comment
            while (ch != '\n') {
                ch = getc(fp); // Keep looping until a newline char is found
                if (ch == '\n') LINE++;
            }
        }
        ch = getc(fp);
        if (ch == '\n') LINE++;
    }
    ungetc(ch, fp);
}
