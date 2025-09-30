#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
Assignment :
lex - Lexical Analyzer for PL /0
Author : Jaden Simmons
Language : C ( only )
To Compile :
gcc - O2 - std = c11
-o lex lex . c
To Execute ( on Eustis ):
./ lex < input file >
where :
< input file > is the path to the PL /0 source program
Notes :
- Implement a lexical analyser for the PL /0 language .
- The program must detect errors such as
- numbers longer than five digits
- identifiers longer than eleven characters
- invalid characters .
- The output format must exactly match the specification .
- Tested on Eustis .
Class : COP 3402 - System Software - Fall 2025
Instructor : Dr . Jie Lin
Due Date : Friday , October 3 , 2025 at 11:59 PM ET
*/

typedef enum
{
    skipsym = 1,
    identsym,
    numbersym,
    plussym,
    minussym,
    multsym,
    slashsym,
    eqsym,
    neqsym,
    lessym,
    leqsym,
    gtrsym,
    geqsym,
    lparentsym,
    rparentsym,
    commasym,
    semicolonsym,
    periodsym,
    becomessym,
    beginsym,
    endsym,
    ifsym,
    fisym,
    thensym,
    whilesym,
    dosym,
    callsym,
    constsym,
    varsym,
    procsym,
    writesym,
    readsym,
    elsesym,
    evensym
} TokenType;

typedef struct Token
{
    char *lexeme;
    int token;
} Token;

Token reservedWordArr[] = {
    {"begin", beginsym},
    {"end", endsym},
    {"if", ifsym},
    {"fi", fisym},
    {"then", thensym},
    {"while", whilesym},
    {"do", dosym},
    {"call", callsym},
    {"const", constsym},
    {"var", varsym},
    {"procedure", procsym},
    {"write", writesym},
    {"read", readsym},
    {"else", elsesym},
    {"even", evensym}};

Token specialSymbolArr[] = {
    {"+", plussym},
    {"-", minussym},
    {"*", multsym},
    {"/", slashsym},
    {"=", eqsym},
    {"<", lessym},
    {">", gtrsym},
    {"(", lparentsym},
    {")", rparentsym},
    {",", commasym},
    {";", semicolonsym},
    {".", periodsym}};

int copySrcToArray(FILE *fp, char **arr, int *arrSize)
{
    int curIndex = 0;
    while (1)
    {
        int c = fgetc(fp); // Get each char from the file

        if (c == EOF)
        {
            return curIndex;
        }

        if (curIndex >= *arrSize)
        {
            *arrSize *= 2;
            *arr = realloc(*arr, *arrSize * sizeof(char));

            if (*arr == NULL)
            {
                printf("Reallocation failed\n");
                return curIndex;
            }
        }

        (*arr)[curIndex] = c;
        curIndex++;
    }
    return curIndex;
}

int checkReservedWords(char *word, int reservedWordArrLen)
{
    for (int j = 0; j < reservedWordArrLen; j++) // For the length of reserved words
    {
        if (strcmp(word, reservedWordArr[j].lexeme) == 0) // If the word is in reserved words print its token
        {
            printf(" %d", reservedWordArr[j].token);
            return reservedWordArr[j].token; // Stops the loop once the word is found
        }
    }
    return 0;
}

int checkSpecialSybols(char symbol, int specialSymbolArrLen)
{
    char s[2] = {symbol, '\0'};
    for (int j = 0; j < specialSymbolArrLen; j++)
    {
        if (strcmp(s, specialSymbolArr[j].lexeme) == 0)
        {
            printf(" %d", specialSymbolArr[j].token);
            return 1;
        }
    }
    return 0;
}

int main()
{
    int reservedWordArrLen = sizeof(reservedWordArr) / sizeof(reservedWordArr[0]);
    int specialSymbolsArrLen = sizeof(specialSymbolArr) / sizeof(specialSymbolArr[0]);

    FILE *fp = fopen("input.txt", "r"); // Open the file

    if (fp == NULL) // If it cant be opened print error
    {
        printf("Error opening file\n");
        return 1;
    }

    // Allocate space for two arrays one for the input file and one for the token list
    int arrSize = 2;                            // Set the initial size of the dynamic array
    int tokenArrSize = 2;
    int tokenListIndex = 0;
    char *arr = malloc(sizeof(char) * arrSize); // Creates a dynamic array to store the input file
    Token *tokenList = malloc(sizeof(char) * tokenArrSize);

    if (arr == NULL) // Check if allocation failed
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    int charsRead = copySrcToArray(fp, &arr, &arrSize); // adds everything from src input file to array and return the last index

    for (int i = 0; i < charsRead; i++)
    {
        if (arr[i] == '/' && arr[i + 1] == '*') // Handles the comment delimiters
        {
            while (arr[i] != '*' && arr[i + 1] != '/')
            {
                i++;
                if (i >= charsRead) // No */ found to close the comment
                {
                    return 1;
                }
            }
        }

        char word[50];
        int wordIndex = 0;
        if (isalpha(arr[i])) // If it is a letter
        {
            while (isalnum(arr[i])) // iterates until anything other than a letter or num is found
            {
                word[wordIndex] = arr[i]; // Add char to word
                i++;
                wordIndex++;
            }
            word[wordIndex] = '\0';
            tokenList[tokenListIndex].lexeme = word;
            printf("%s", word);

            int tokenVal = checkReservedWords(word, reservedWordArrLen);

            if (tokenVal == 0)
            { // If it is not a word then it must be a identifier
                printf(" %d", identsym);
                tokenVal = identsym;
            }

            tokenList[tokenListIndex].token = tokenVal;
            tokenListIndex++;
            printf("\n");
        }

        //todo Check if it is a number

        // First check for double char symbols
        if (arr[i] == '<' && arr[i + 1] == '>') // neqsym
        {
            printf("%c%c", arr[i], arr[i + 1]);
            printf(" %d", neqsym);
            i++;
        }
        else if (arr[i] == '<' && arr[i + 1] == '=') // leqsym
        {
            printf("%c%c", arr[i], arr[i + 1]);
            printf(" %d", leqsym);
            i++;
        }
        else if (arr[i] == '>' && arr[i + 1] == '=') // geqsym
        {
            printf("%c%c", arr[i], arr[i + 1]);
            printf(" %d", geqsym);
            i++;
        }
        else if (arr[i] == ':' && arr[i + 1] == '=') // becomesym
        {
            printf("%c%c", arr[i], arr[i + 1]);
            printf(" %d", becomessym);
            i++;
        }
        else // otherwise search through single char symbols
        {
            printf("%c", arr[i]);
            int isSymbol = checkSpecialSybols(arr[i], specialSymbolsArrLen);

            if (!isSymbol)
            { // If not a symbol then it must be a lexical error

            }
        }
        printf("\n");
    }
    return 0;
}
