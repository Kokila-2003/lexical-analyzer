# 🔍 Lexical Analyzer in C

## 📌 Project Overview

This project implements a Lexical Analyzer (Scanner) in C.  
A lexical analyzer is the first phase of a compiler. It reads a C source file character by character and converts the input stream into meaningful tokens.

The analyzer identifies and classifies various token types such as keywords, identifiers, numbers, operators, symbols, string literals, character literals, and comments.

---

## 🧠 Introduction

In compiler design, lexical analysis is the process of converting a sequence of characters into a sequence of tokens.  
Each token represents a logical unit of the programming language.

The lexical analyzer:

- Reads input using file handling functions.
- Removes whitespace and comments.
- Groups characters into valid tokens.
- Classifies each token into predefined categories.
- Prints token type and its lexeme.

---

## 🏗️ Project Structure

The project consists of the following files:

main.c  
lexer.c  
lexer.h  
README.md  

### File Description

**main.c**
- Accepts source file name using command-line arguments.
- Opens the file using `fopen()`.
- Calls `analyzeFile()`.
- Closes the file.

**lexer.c**
- Contains the lexical analysis logic.
- Implements all token-handling functions.
- Uses modular design for better readability.

**lexer.h**
- Defines `TokenType` enum.
- Defines `Token` structure.
- Contains function declarations.

---

## 🧩 Supported Token Types

The lexical analyzer recognizes the following tokens:

### 1. Keywords
Reserved words of C language such as:
int, float, char, double, return, if, else, for, while, void, const

### 2. Identifiers
Names of variables and functions.
Example:
main, x, value1

### 3. Numbers
- Integer values → 10, 250, 0  
- Floating-point values → 3.14, 0.25, 10.5  

### 4. Operators
Single-character operators:
+  -  *  /  =  <  >  !

Double-character operators:
==  !=  <=  >=  ++  --

### 5. Symbols
( ) { } [ ] ; , .

### 6. String Literals
Text enclosed in double quotes:
"Hello"

### 7. Character Literals
Characters enclosed in single quotes:
'A'
'\n'

### 8. Comments
Single-line comments:
 // comment

Multi-line comments:
 /* comment */

Comments are ignored during tokenization.

---

## ⚙️ Working Principle

1. Open the input source file.
2. Read characters using `fgetc()`.
3. Ignore whitespace characters.
4. Identify the starting character of a token.
5. Call the corresponding handler function.
6. Store the lexeme in a buffer.
7. Classify the token using `TokenType`.
8. Print token type and lexeme.
9. Continue until end of file.

---

## 🧱 Modular Design

Each token category is handled by a separate function:

- handleIdentifier()
- handleNumber()
- handleString()
- handleChar()
- handleOperator()
- handleSymbol()
- handleCommentOrDivision()

This modular structure improves:

- Code clarity
- Maintainability
- Debugging
- Scalability

---

## 💻 Compilation and Execution

Compile the project using GCC:

gcc main.c lexer.c -o lexer

Run the program:

./lexer input.c

Example:

./lexer test.c

---

## 🧪 Example Input

int main() {
    int x = 10;
    float y = 3.14;
    char c = 'A';
    printf("Hello");
    x++;
}

---

## 📤 Example Output

Keyword : int  
Identifier : main  
Symbol : (  
Symbol : )  
Symbol : {  
Keyword : int  
Identifier : x  
Operator : =  
Number : 10  
Symbol : ;  
Keyword : float  
Identifier : y  
Operator : =  
Number : 3.14  
Symbol : ;  
Keyword : char  
Identifier : c  
Operator : =  
Character : A  
Symbol : ;  
Identifier : printf  
Symbol : (  
String : Hello  
Symbol : )  
Symbol : ;  
Identifier : x  
Operator : ++  
Symbol : ;  
Symbol : }

---

## 📚 Concepts Used

- File Handling (fopen, fgetc, ungetc)
- Structures (struct)
- Enumeration (enum)
- String Handling (strcmp, strcpy)
- Modular Programming
- Lookahead Technique for multi-character operators
- Token classification logic

---

## 🚀 Possible Enhancements

- Line number tracking
- Improved error handling
- Preprocessor directive support
- Support for hexadecimal and octal numbers
- Symbol table implementation

---

## ✅ Conclusion

The Lexical Analyzer was successfully implemented in C.  
The program correctly reads a C source file, identifies tokens, and classifies them according to their type using a modular design approach.

This project demonstrates the fundamental working of the lexical analysis phase in compiler design.