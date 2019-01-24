#include "types.h"
#include "lexeme.h"
#include "scanner.h"
#include "lex.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

Lexeme* lex(FILE* fp)
{
    int ch;
    skipWhiteSpace(fp);

    ch = getc(fp);
    if (ch == EOF) return newLexemeChar(END_OF_INPUT, ch);

    switch(ch) {
        // single character tokens

        case '(': return newLexemeChar(OPAREN, ch);
        case ')': return newLexemeChar(CPAREN, ch);
        case ',': return newLexemeChar(COMMA, ch);
        case '+': return newLexemeChar(PLUS, ch);
        case '-': return newLexemeChar(MINUS, ch);
        case '*': return newLexemeChar(TIMES, ch);
        case '/': return newLexemeChar(DIVIDES, ch);
        case '%': return newLexemeChar(MODULUS, ch);
        case '>': return newLexemeChar(GREATERTHAN, ch);
        case '<': return newLexemeChar(LESSTHAN, ch);
        case '.': return newLexemeChar(DOT, ch);
        case '#': return newLexemeChar(HASH, ch);
        case '[': return newLexemeChar(OBRACKET, ch);
        case ']': return newLexemeChar(CBRACKET, ch);
        // TODO add other single characters

        default:
            if (ch == '=') {
                int ch2 = getc(fp);
                if (ch2 == '=') return newLexemeWord(EQUALS, "==");
                else {
                    ungetc(ch2, fp);
                    return newLexemeChar(ASSIGN, ch);
                }
            }
            if (isdigit(ch)) {
                ungetc(ch, fp);
                return lexNumber(fp);
            }
            else if (isalpha(ch)) {
                ungetc(ch, fp);
                return lexVariableOrKeyword(fp);
            }
            else if (ch == '\"') {
                return lexString(fp);
            }
            else {
                return newLexemeChar(UNKNOWN, ch);
            }
    }
}

Lexeme* lexNumber(FILE* fp)
{
    int real = 0;
    int ch;
    char buffer[64] = "";
    int count = 0;

    ch = getc(fp);
    while ((ch != EOF) && (isdigit(ch) || ch == '.')) {
        count++;
        if (count > 63) {
            printf("ERROR: TOO MANY CHARS");
            exit(0);
        }

        buffer[strlen(buffer)] = ch;
        if (ch == '.') {
            int ch2 = getc(fp);
            if (isdigit(ch2)) {
                if (real) return newLexemeWord(BADNUMBER, buffer);
                real = 1;
                ungetc(ch2, fp);
            }
            else {
                ungetc(ch2, fp);
                ungetc(ch, fp);
                break;
            }
        }
        ch = getc(fp);
    }
    if (ch == ')' || ch == ']') ungetc(ch, fp);

    if (real) return newLexemeWord(REAL, buffer);
    else return newLexemeWord(INTEGER, buffer);
}

Lexeme* lexVariableOrKeyword(FILE* fp)
{
    int ch;
    char buffer[64] = "";
    int count = 0;

    ch = getc(fp);
    while (isalnum(ch)) {
        count++;
        if (count > 63) {
            printf("ERROR: TOO MANY CHARS");
            exit(0);
        }

        buffer[strlen(buffer)] = ch;
        ch = getc(fp);
    }
    ungetc(ch, fp);

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
    else if (strcmp(buffer, "return") == 0) {
        return newLexemeWord(RETURN, buffer);
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
    while ((ch != EOF) && (ch != '\"')) {
        if (index == length) {
            buffer = realloc(buffer, sizeof(char) * length * 2 + 1);
            length *= 2;
        }

        buffer[index++] = ch;
        buffer[index] = '\0';
        ch = getc(fp);
    }
    return newLexemeWord(STRING, buffer);
}

void skipWhiteSpace(FILE* fp)
{
    int ch;
    ch = getc(fp);

    while (isspace(ch) || ch == '#') {
        if (ch == '#') { // Start of a comment
            while (ch != '\n') ch = getc(fp); // Keep looping until a newline char is found
        }
        ch = getc(fp);
    }
    ungetc(ch, fp);
}
