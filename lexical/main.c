/*
====================================================================
MAIN MODULE - LEXICAL ANALYZER
====================================================================

This file contains the main entry point of the lexical analyzer
program.

The main function performs the following tasks:

1. Accepts the source file name through command line arguments.
2. Opens the file in read mode.
3. Calls the lexical analyzer function to process the file.
4. Closes the file after analysis is complete.

====================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

/*
--------------------------------------------------------------------
FUNCTION: main
--------------------------------------------------------------------
Description:
This is the starting point of the program.

The function accepts the source file name from the command line.
It then opens the file and passes the file pointer to the
analyzeFile() function which performs lexical analysis.

Steps performed:
1. Check whether the correct number of arguments is provided.
2. Open the source file using fopen().
3. If the file cannot be opened, print an error message.
4. Call analyzeFile() to start lexical analysis.
5. Close the file using fclose().

Parameters:
argc - argument count
argv - argument vector containing command line arguments

Return:
0 - if program execution fails
1 - if program executes successfully
--------------------------------------------------------------------
*/

int main(int argc, char *argv[])
{
    /* Check if user provided correct command line arguments */
    if(argc != 2)
    {
        printf("Usage: ./lexer <sourcefile>\n");
        return 1;
    }

    /* Open the source file in read mode */
    FILE *fp = fopen(argv[1], "r");

    /* Check if file opening failed */
    if(fp == NULL)
    {
        perror("ERROR");
        return 0;
    }

    /* Call lexical analyzer to process the source file */
    analyzeFile(fp);

    /* Close the source file */
    fclose(fp);

    return 1;
}