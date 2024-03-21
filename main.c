#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <stdint.h>
#include <windows.h>




void prompt() {
    printf("prompt$: ");
}


void cmatrix() {
    while (1) {
        // Clear screen
        printf("\033[2J");

        // Seed the random number generator with current time
        srand(time(NULL));

        // Generate matrix-like output
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 200; j++) {
                if (rand() % 20 == 0) // Randomly print characters
                    printf("%c", rand() % 94 + 33); // No color
                else
                    printf(" "); // Empty space
            }
            printf("\n");
        }

        fflush(stdout);
        usleep(100000); // Wait for 100 milliseconds before updating again
    }
}


static void wc(char* fileName, int countLines, int countWords, int countChars){
    int lineCount = 0;
    int wordCount = 0;
    int characterCount = 0;
    char c;
    int inWord = 0;

    FILE *file = fopen(fileName, "r");

    if(file == NULL){
        printf("Error: Unable to read file!");
        return;
    }

    while((c = fgetc(file)) != EOF){
        characterCount++;

        if(c == '\n'){
            lineCount++;
        }

        if(isspace(c)){
            if(inWord){
                wordCount++;
                inWord = 0;
            }
        } else {
            inWord = 1;
        }
    }

    if (inWord) {
        wordCount++; // Count the last word if the file doesn't end with whitespace
    }

    fclose(file);

    if (countLines) {
        printf("Lines: %d\n", lineCount);
    }
    if (countWords) {
        printf("Words: %d\n", wordCount);
    }
    if (countChars) {
        printf("Characters: %d\n", characterCount);
    }
}

void grep(char* pattern, char* fileName) {
    // Implement grep command logic here
    printf("Executing grep command for pattern: %s in file: %s\n", pattern, fileName);
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error: Unable to read file: %s\n", fileName);
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }
    fclose(file);
}


void parseInput(char *input) {
    // Tokenization
    char *token = strtok(input, " \n"); // Break input into tokens separated by space or newline

    // First token is the command
    char *command = token;

    // Subsequent tokens are arguments
    while (token != NULL) {
        token = strtok(NULL, " \n"); // Get next token
        if (token != NULL) {
            printf("%s\n", token); // Print arguments
        }

        if (strcmp(command, "wc") == 0) {
            // Parse options and filename for wc command
            int countLines = 0;
            int countWords = 0;
            int countChars = 0;
            char *fileName = NULL;

            while (token != NULL) {
                if (strcmp(token, "-l") == 0) {
                    countLines = 1;
                } else if (strcmp(token, "-w") == 0) {
                    countWords = 1;
                } else if (strcmp(token, "-c") == 0) {
                    countChars = 1;
                } else {
                    // Assume this token is the filename
                    fileName = token;
                    break;
                }
                token = strtok(NULL, " \n"); // Move to the next token
            }

            if (fileName != NULL) {
                // Call wc function with parsed arguments
                wc(fileName, countLines, countWords, countChars);
            } else {
                printf("Usage: wc [-l] [-w] [-c] <filename>\n");
            }
        } else if (strcmp(command, "grep") == 0) {
            // Implementation for grep command already exists
            char *pattern = token;
            token = strtok(NULL, " \n");
            if (token != NULL) {
                char *fileName = token;
                grep(pattern, fileName);
            } else {
                printf("Usage: grep <pattern> <filename>\n");
            }
        } else if (strcmp(command, "cmatrix") == 0){
            cmatrix();
        } else if (strcmp(command, "df") == 0){
            // fali df
        } else {
            printf("Command not found: %s\n", command);
        }
    }
}


int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole,
                            FOREGROUND_RED);
    while(1){
        char input[200];
        prompt();
        fgets(input, sizeof(input), stdin);
        parseInput(input);
    }
    return 0;
}

