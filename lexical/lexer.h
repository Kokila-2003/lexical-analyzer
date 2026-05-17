#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#define MAX_TOKEN 100

typedef enum
{
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_SYMBOL,
    TOKEN_STRING,
    TOKEN_CHAR
} TokenType;

typedef struct
{
    TokenType type;
    char lexeme[MAX_TOKEN];
} Token;

void analyzeFile(FILE *);

void handleIdentifier(FILE *, char);
void handleNumber(FILE *, char);
void handleString(FILE *);
void handleChar(FILE *);
void handleCommentOrDivision(FILE *);
void handleOperator(FILE *, char);
void handleSymbol(char);

int isKeyword(char[]);
void printToken(Token);

#endif