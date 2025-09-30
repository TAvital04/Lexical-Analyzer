/*
    Assignment:
        lex - Lexical Analyzer for PL/0

    Author:
        Tal Avital

    Language: 
        C(only)

    To Compile:
        gcc -O2 -std=c11 -o lex lex.c

    To Execute (on Eustis ):
        ./lex <input file >
        where:
            <input file > is the path to the PL/0 source program
            
    Notes:
        - Implement a lexical analyser for the PL/0 language.
        - The program must detect errors such as
        - numbers longer than five digits
        - identifiers longer than eleven characters
        - invalid characters.
        - The output format must exactly match the specification.
        - Tested on Eustis.

    Class: COP 3402 - System Software - Fall 2025
    Instructor: Dr. Jie Lin

    Due Date: Friday , October 3, 2025 at 11:59 PM ET
*/

// Imports
#include <stdio.h>
#include <stdlib.h>

// Definitions and global variables
#define PROGRAM_SIZE 500
#define TOKEN_SIZE 12

static char program[PROGRAM_SIZE];
static char *tokens[PROGRAM_SIZE][TOKEN_SIZE];

// Function prototypes
int isSpace(char c);
int isNumber(int n);
void toToken(char *string, int tokensIndex);

// Main
int main(int argc, char *argv[]) {
    // Validate command line arguments
    if(argc != 2) {
        fprintf(stderr,
            "Error: This file takes in one argument; the name of an input file"
        );
        exit(1);
    }

    // Declare variables
    int programIndex = 0;
    int tokensIndex = 0;

    // Open the input file
        // Store the file name
        char *inputFileName = argv[1];

        // Attempt to open the file
        FILE *inputFile = fopen(inputFileName, "r");

        // Validate the file
        if(!inputFile) {
            fprintf(stderr,
                "Error: File not found"
            );
            exit(1);
        }

    // Read the file
        // Store file contents in program, print to console
        printf("Source Program:\n\n");

        char c;
        int count = 1;
        while(fscanf(inputFile, "%c", &c) == 1) {
            // Print the character to the console
            printf("%c", c);

            // Add the character to the program if it is not a space
            if(!isSpace(c)) {
                program[count] = c;
                r++;
            }

            // Store the program file size at the first index of the array
            program[0] = count - 1;
        }

        printf("\n\n");

    // Parse the program
        printf("Lexeme Table:\n\n");
        printf("lexeme\ttoken type\n")

        for(programIndex; programIndex < program[0]; programIndex++) {
            // Declare variables
            int temp;
            char token[TOKEN_SIZE];

            // If the current index is the start of a number
            if(isNumber(program[programIndex])) {
                // Store the number
                for(temp = 0; isNumber(program[temp + programIndex]); temp++) {
                    if(temp < 5) {
                        token[temp] = program[temp + programIndex]
                    }
                }

                // Handle valid and invalid cases
                if(temp > 5) {
                    toToken("1", tokenIndex++);
                } else {
                    toToken("3", tokenIndex++);

                    token[temp] = '\0';
                    toToken(token, tokenIndex++);
                }
            } else {
                // Store the string
                for(temp = 0; temp )
            }
        }
}

int isSpace(char c) {
    return (
        c == ' ' ||
        c == '\t' ||
        c == '\n' ||
        c == '\v' ||
        c == '\f' ||
        c == '\r'
    )
}

int isNumber(int n) {
    return (n >= 48 && n <= 57)
}

void toToken(char *string, int tokensIndex) {
    for(int i = 0; string[i] != '\0'; i++) {
        tokens[tokensIndex][i] = string[i];
    }
}