/*
====================================================================
LEXICAL ANALYZER MODULE
====================================================================

This file implements the lexical analysis phase of a simple
compiler. It reads a C source file and classifies tokens such as
keywords, identifiers, numbers, operators, symbols, string literals,
character literals, and comments.

Each token category is processed by a separate handler function,
making the implementation modular and easier to maintain.

====================================================================
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

/*
--------------------------------------------------------------------
FUNCTION: analyzeFile
--------------------------------------------------------------------
Description:
This is the main driver function of the lexical analyzer.

It reads the source file character by character using fgetc() and
determines the category of each token.

Based on the first character of a token, this function calls the
appropriate handler function such as:

- handleIdentifier()  → for identifiers and keywords
- handleNumber()      → for numeric values
- handleString()      → for string literals
- handleChar()        → for character literals
- handleOperator()    → for operators
- handleSymbol()      → for punctuation symbols
- handleCommentOrDivision() → for comments or division operator

Whitespace and preprocessor directives are ignored.

Parameters:
fp - pointer to the input source file

Return:
None
--------------------------------------------------------------------
*/
void analyzeFile(FILE *fp)
{
    char ch;

    while((ch = fgetc(fp)) != EOF)
    {
        if(ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
            continue;

        else if(ch == '#')
        {
            while((ch = fgetc(fp)) != EOF && ch != '\n');
        }    

        else if(isalpha(ch))
            handleIdentifier(fp, ch);

        else if(isdigit(ch))
            handleNumber(fp, ch);

        else if(ch == '"')
            handleString(fp);

        else if(ch == '\'')
            handleChar(fp);

        else if(ch == '/')
            handleCommentOrDivision(fp);

        else if(ch == '(' || 
                ch == ')' || 
                ch == '[' || 
                ch == ']' ||
                ch == '{' || 
                ch == '}' || 
                ch == ';' || 
                ch == '.' || 
                ch == ',')
            handleSymbol(ch);

        else if(ch == '+' || 
                ch == '-' || 
                ch == '*' ||
                ch == '=' || 
                ch == '>' || 
                ch == '<' || 
                ch == '!')
            handleOperator(fp, ch);
        else
            printf("Unknown character : %c\n", ch);
    }
}



/*
--------------------------------------------------------------------
FUNCTION: handleIdentifier
--------------------------------------------------------------------
Description:
This function processes identifiers and keywords.

When the lexical analyzer encounters a letter, it calls this
function to read the complete identifier.

The function continues reading characters while they are
letters or digits.

After forming the word, it checks whether the word is a
keyword using the isKeyword() function.

If the word is a keyword:
    token type = TOKEN_KEYWORD

Otherwise:
    token type = TOKEN_IDENTIFIER

Parameters:
fp - file pointer used to read additional characters
ch - first character of the identifier

Return:
None
--------------------------------------------------------------------
*/
void handleIdentifier(FILE *fp, char ch)
{
    char buffer[MAX_TOKEN];
    int i = 0;

    buffer[i++] = ch;

    while((ch = fgetc(fp)) != EOF)
    {
        if((ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z') ||
           (ch >= '0' && ch <= '9'))
        {
            buffer[i++] = ch;
        }
        else
            break;
    }

    if(ch != EOF)
        ungetc(ch, fp);

    buffer[i] = '\0';

    Token token;

    if(isKeyword(buffer))
        token.type = TOKEN_KEYWORD;
    else
        token.type = TOKEN_IDENTIFIER;

    strcpy(token.lexeme, buffer);
    printToken(token);
}



/*
--------------------------------------------------------------------
FUNCTION: handleNumber
--------------------------------------------------------------------
Description:
This function processes numeric tokens.

It reads digits continuously to form an integer value.

If a decimal point (.) is encountered, the function continues
reading digits to form a floating point number.

Examples:
10
25
3.14
0.5

Parameters:
fp - file pointer
ch - first digit of the number

Return:
None
--------------------------------------------------------------------
*/
void handleNumber(FILE *fp, char ch)
{
    char buffer[MAX_TOKEN];
    int i = 0;

    buffer[i++] = ch;

    while((ch = fgetc(fp)) != EOF &&
          (ch >= '0' && ch <= '9'))
    {
        buffer[i++] = ch;
    }

    if(ch == '.')
    {
        buffer[i++] = ch;

        while((ch = fgetc(fp)) != EOF &&
              (ch >= '0' && ch <= '9'))
        {
            buffer[i++] = ch;
        }
    }

    if(ch != EOF)
        ungetc(ch, fp);

    buffer[i] = '\0';

    Token token;
    token.type = TOKEN_NUMBER;
    strcpy(token.lexeme, buffer);
    printToken(token);
}



/*
--------------------------------------------------------------------
FUNCTION: handleSymbol
--------------------------------------------------------------------
Description:
This function handles punctuation symbols in the source code.

Symbols include:
( ) { } [ ] ; , .

Each symbol is treated as a separate token.

Parameters:
ch - the symbol character detected in the input

Return:
None
--------------------------------------------------------------------
*/
void handleSymbol(char ch)
{
    char buffer[2];

    buffer[0] = ch;
    buffer[1] = '\0';

    Token token;
    token.type = TOKEN_SYMBOL;
    strcpy(token.lexeme, buffer);
    printToken(token);
}



/*
--------------------------------------------------------------------
FUNCTION: handleString
--------------------------------------------------------------------
Description:
This function processes string literals.

When a double quote (") is encountered, the lexer calls this
function to read characters until the closing quote is found.

The characters between the quotes are stored as the string lexeme.

Example:
"Hello World"

Parameters:
fp - file pointer

Return:
None
--------------------------------------------------------------------
*/
void handleString(FILE *fp)
{
    char buffer[MAX_TOKEN];
    int i = 0;
    char ch;

    while((ch = fgetc(fp)) != EOF)
    {
        if(ch == '"')
            break;
        else
            buffer[i++] = ch;
    }

    buffer[i] = '\0';

    Token token;
    token.type = TOKEN_STRING;
    strcpy(token.lexeme, buffer);
    printToken(token);
}



/*
--------------------------------------------------------------------
FUNCTION: handleChar
--------------------------------------------------------------------
Description:
This function processes character literals.

Character literals are enclosed within single quotes.

Examples:
'A'
'\n'
'\t'

The function reads the character between the quotes and stores
it as a character token.

Parameters:
fp - file pointer

Return:
None
--------------------------------------------------------------------
*/
void handleChar(FILE *fp)
{
    char buffer[MAX_TOKEN];
    int i = 0;
    char ch;

    ch = fgetc(fp);

    if(ch == '\\')
    {
        buffer[i++] = ch;
        ch = fgetc(fp);
        buffer[i++] = ch;
        ch = fgetc(fp);
    }
    else
    {
        buffer[i++] = ch;
        ch = fgetc(fp);
    }

    buffer[i] = '\0';

    Token token;
    token.type = TOKEN_CHAR;
    strcpy(token.lexeme, buffer);
    printToken(token);
}



/*
--------------------------------------------------------------------
FUNCTION: handleCommentOrDivision
--------------------------------------------------------------------
Description:
This function handles comments and the division operator.

When '/' is encountered, the lexer checks the next character.

Possible cases:

1. "//" - single line comment
   The lexer skips characters until the end of the line.

2. Multi-line comment (slash-star ... star-slash)
   The lexer skips characters until the closing comment marker.

3. "/" - division operator
   If it is not part of a comment, it is treated as an operator.

Parameters:
fp - file pointer

Return:
None
--------------------------------------------------------------------
*/
void handleCommentOrDivision(FILE *fp)
{
    char buffer[2];
    char ch, next;

    next = fgetc(fp);

    if(next == '/')
    {
        while((ch = fgetc(fp)) != EOF && ch != '\n');
    }
    else if(next == '*')
    {
        while((ch = fgetc(fp)) != EOF)
        {
            if(ch == '*')
            {
                next = fgetc(fp);
                if(next == '/')
                    break;
                else
                    ungetc(next, fp);
            }
        }
    }
    else
    {
        if(next != EOF)
            ungetc(next, fp);

        buffer[0] = '/';
        buffer[1] = '\0';

        Token token;
        token.type = TOKEN_OPERATOR;
        strcpy(token.lexeme, buffer);
        printToken(token);
    }
}



/*
--------------------------------------------------------------------
FUNCTION: handleOperator
--------------------------------------------------------------------
Description:
This function processes operators.

It supports both single-character and double-character operators.

Single operators:
+  -  *  /  =  <  >  !

Double operators:
==  !=  <=  >=  ++  --

The function checks the next character to determine whether
the operator consists of one or two characters.

Parameters:
fp - file pointer
ch - first operator character

Return:
None
--------------------------------------------------------------------
*/
void handleOperator(FILE *fp, char ch)
{
    char buffer[3];
    int i = 0;
    char next;

    buffer[i++] = ch;

    next = fgetc(fp);

    if((ch == '=' && next == '=') ||
       (ch == '!' && next == '=') ||
       (ch == '<' && next == '=') ||
       (ch == '>' && next == '=') ||
       (ch == '+' && next == '+') ||
       (ch == '-' && next == '-'))
    {
        buffer[i++] = next;
    }
    else
    {
        if(next != EOF)
            ungetc(next, fp);
    }

    buffer[i] = '\0';

    Token token;
    token.type = TOKEN_OPERATOR;
    strcpy(token.lexeme, buffer);
    printToken(token);
}



/*
--------------------------------------------------------------------
FUNCTION: printToken
--------------------------------------------------------------------
Description:
This function prints the identified token and its lexeme.

Based on the token type stored in the Token structure, it prints
the corresponding token category.

Example output:

Keyword : int
Identifier : x
Operator : =
Number : 10

Parameters:
token - structure containing token type and lexeme

Return:
None
--------------------------------------------------------------------
*/
void printToken(Token token)
{
    switch(token.type)
    {
        case TOKEN_KEYWORD:
            printf("Keyword : %s\n", token.lexeme);
            break;

        case TOKEN_IDENTIFIER:
            printf("Identifier : %s\n", token.lexeme);
            break;

        case TOKEN_NUMBER:
            printf("Number : %s\n", token.lexeme);
            break;

        case TOKEN_OPERATOR:
            printf("Operator : %s\n", token.lexeme);
            break;

        case TOKEN_SYMBOL:
            printf("Symbol : %s\n", token.lexeme);
            break;

        case TOKEN_STRING:
            printf("String : %s\n", token.lexeme);
            break;
        
        case TOKEN_CHAR:
            printf("Character : %s\n", token.lexeme);
            break;    

        default:
            printf("Unknown : %s\n", token.lexeme);
    }
}



/*
--------------------------------------------------------------------
FUNCTION: isKeyword
--------------------------------------------------------------------
Description:
This function checks whether a given word is a reserved keyword
in the C language.

It compares the word with a predefined list of keywords using
strcmp().

If the word matches a keyword, the function returns 1.
Otherwise, it returns 0.

Parameters:
word - the identifier string to be checked

Return:
1 - if the word is a keyword
0 - if the word is not a keyword
--------------------------------------------------------------------
*/
int isKeyword(char word[])
{
    char *keywords[] = {
        "int", "float", "char", "double",
        "return", "if", "else", "for",
        "while", "void", "const"
    };

    int size = 11;
    int i;

    for(i = 0; i < size; i++)
    {
        if(strcmp(word, keywords[i]) == 0)
            return 1;
    }

    return 0;
}