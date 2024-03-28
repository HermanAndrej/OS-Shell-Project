#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <stdint.h>
#include <errno.h>
#include <dirent.h>
#include <sys/wait.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h> // For Unix-like systems
#endif

#define ANSI_BG_MAGENTA    "\x1b[45m" // background
#define ANSI_COLOR_RED     "\x1b[31m" // text

void handleOutputRedirection(char *input) {
    char *redirect_symbol = strchr(input, '>');
    if (redirect_symbol != NULL) {
        // Extract the filename for redirection
        *redirect_symbol = '\0'; // Replace '>' with NULL character
        char *filename = redirect_symbol + 1; // Filename starts right after '>'
        // Trim leading and trailing spaces from filename
        while (isspace(*filename)) {
            filename++;
        }
        int len = strlen(filename);
        while (len > 0 && isspace(filename[len - 1])) {
            filename[--len] = '\0';
        }


        // Redirect output to the specified file
        freopen(filename, "w", stdout);
        fflush(stdout);
    }
}

void help() {
    printf("Available commands and their purposes:\n");
    printf("1. wc - Count lines, words, and characters in a file.\n");
    printf("   Usage: wc [-l] [-w] [-c] <filename>\n");
    printf("2. grep - Search for a pattern in a file.\n");
    printf("   Usage: grep <pattern> <filename>\n");
    printf("3. cmatrix - Display a scrolling 'Matrix' like effect.\n");
    printf("   Usage: cmatrix\n");
    printf("4. df - Display disk space usage.\n");
    printf("   Usage: df\n");
    printf("5. tiger - Display ASCII art of a tiger.\n");
    printf("   Usage: tiger\n");
    printf("6. pokemon - Display ASCII art of a Pokemon.\n");
    printf("   Usage: pokemon\n");
    printf("7. thirsty - Display ASCII art of a drink.\n");
    printf("   Usage: thirsty\n");
    printf("8. pwgen - Generate a random password of specified length.\n");
    printf("   Usage: pwgen <length>\n");
    printf("9. help - Display usage and purpose of each command.\n");
    printf("   Usage: help\n");
}

void prompt() {
    char hostname[256];
    char *username;

    printf(ANSI_COLOR_RED);

    // Get the machine name
    gethostname(hostname, sizeof(hostname));

    // Get the username
    username = getlogin();

    // Print the prompt
    printf("%s@%s:~$ ", username, hostname);
}

void ls(const char *path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir == NULL) {
        fprintf(stderr, "ls: cannot open directory '%s'\n", path);
        return;
    }

    printf("Listing of directory: %s\n", path);
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

void tiger() {
    char asciiArt[14][60] = {
            "                    __,,,,_",
            "       _ __..-;''`--/'/ /.',-`-.",
            "   (`/' ` |  \\ \\ \\ \\ / / / / .-'/`,_",
            "  /'`\\ \\   |  \\ | \\| // // / -.,/_,'-,",
            " /<7' ;  \\ \\  | ; ||/ /| | \\/    |`-/,/-.,_,/')",
            "/  _.-, `,-\\,__|  _-| / \\ \\/|_/  |    '-/.;.'\\'",
            "`-`  f/ ;      / __/ \\__ `/ |__/ |",
            "     `-'      |  -| =|\\_  \\  |-' |",
            "           __/   /_..-' `  ),'  //",
            "       fL ((__.-'((___..-'' \\__.'"
    };

    for (int i = 0; i < 10; ++i) {
        printf("%s\n", asciiArt[i]);
    }
}

void pokemon() {
    printf("                                  ,'\\\n");
    printf("    _.----.        ____         ,'  _\\   ___    ___     ____\n");
    printf(" _,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`.\n");
    printf("\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |\n");
    printf(" \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |\n");
    printf("   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |\n");
    printf("    \\     ,'-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |\n");
    printf("     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |\n");
    printf("      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |\n");
    printf("       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |\n");
    printf("        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |\n");
    printf("                                `'                            '-._|\n");
    printf("               _,........__\n");
    printf("            ,-'            \"`-.\n");
    printf("          ,'                   `-. \n");
    printf("        ,'                        \\\n");
    printf("      ,'                           .\n");
    printf("      .\\               ,\"\".       `\n");
    printf("     ._.'|             / |  `       \\\n");
    printf("     |   |            `-.'  ||       `.\n");
    printf("     |   |            '-._,'||       | \\\n");
    printf("     .`.,'             `..,'.'       , |`-.\n");
    printf("     l                       .'`.  _/  |   `.\n");
    printf("     `-.._'-   ,          _ _'   -\" \\  .     `\n");
    printf("`.\"\"\"\"\"'-.`-...,---------','         `. `....__.\n");
    printf(".'        `\"-..___      __,'\\          \\  \\     \\\n");
    printf("\\_ .          |   `\"\"\"'    `.           . \\     \\\n");
    printf("  `.          |              `.          |  .     L\n");
    printf("    `.        |`--...________.'.        j   |     |\n");
    printf("      `._    .'      |          `.     .|   ,     |\n");
    printf("         `--,\\       .            `7\"' |  ,      |\n");
    printf("            ` `      `            /     |  |      |    _,-'\"\"`-.\n");
    printf("             \\ `.     .          /      |  '      |  ,'          `.\n");
    printf("              \\  v.__  .        '       .   \\    /| /              \\\n");
    printf("               \\/    `\"\"\"\"\"\"\"\"`.       \\   \\  /.''                |\n");
    printf("                `        .        `._ ___,j.  `/ .-       ,---.     |\n");
    printf("                 ,`-.      \\         .\"     `.  |/        j     `    |\n");
    printf("                /    `.     \\       /         \\ /         |     /    j\n");
    printf("               |       `-.   7-.._ .          |\"          '         /\n");
    printf("               |          `./_    `|          |            .     _,\n");
    printf("               `.           / `----|          |-............`---'\n");
    printf("                 \\          \\      |          |\n");
    printf("                ,'           )     `.         |\n");
    printf("                 7____,,..--'      /          |\n");
    printf("                                  `---.__,--.'\n");
}

void thirsty() {
    printf("                   o           o\n");
    printf("                      o   o\n");
    printf("                         o         o\n");
    printf("\n");
    printf("                     o       o  o\n");
    printf("                  ________._____________\n");
    printf("                  |   .                |\n");
    printf("                  |^^^.^^^^^.^^^^^^.^^^|\n");
    printf("                  |     .   .   .      |\n");
    printf("                   \\      . . . .     /\n");
    printf("C H E E R S !!!      \\     .  .     / \n");
    printf("                       \\    ..    / \n");
    printf("                         \\      / \n");
    printf("                           \\  / \n");
    printf("                            \\/ \n");
    printf("                            ||\n");
    printf("                            ||\n");
    printf("                            ||\n");
    printf("                            ||\n");
    printf("                            ||\n");
    printf("                            /\\\n");
    printf("                           /;;\\\n");
    printf("                      ==============\n");
}

void df(const char *drive) {

#ifdef __unix__
    char command[100];
    snprintf(command, sizeof(command), "df -h %s", drive);

    FILE *pipe = popen(command, "r");
    if (pipe == NULL) {
        printf("Error executing df command\n");
        return;
    }

    char output[512];
    while (fgets(output, sizeof(output), pipe) != NULL) {
        printf("%s", output);
    }

    pclose(pipe);
#else
    // For Windows
    ULARGE_INTEGER total_bytes;
    ULARGE_INTEGER free_bytes;

    if (GetDiskFreeSpaceEx(drive, NULL, &total_bytes, &free_bytes)) {
        printf("Drive %s:\n", drive);
        printf("Total space: %llu bytes\n", total_bytes.QuadPart);
        printf("Free space : %llu bytes\n", free_bytes.QuadPart);
        printf("Used space : %llu bytes\n", total_bytes.QuadPart - free_bytes.QuadPart);
        printf("Usage      : %.2f%%\n", ((double)(total_bytes.QuadPart - free_bytes.QuadPart) / total_bytes.QuadPart) * 100);
    } else {
        printf("Error getting disk space information for drive %s\n", drive);
    }
#endif
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
        usleep(50000); // Wait for 50 milliseconds before updating again
    }
}

void wc(char* fileName, int countLines, int countWords, int countChars){
    int lineCount = 0;
    int wordCount = 0;
    int characterCount = 0;
    char c;
    int inWord = 0;

    FILE *file = fopen(fileName, "r");

    if(file == NULL){
        printf("Error: Unable to read file!\n");
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

void pwgen(int length) {
    // Define character set for password generation
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+";

    // Calculate the size of the character set
    int charset_size = sizeof(charset) - 1;

    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Generate and print the password
    printf("Generated Password: ");
    for (int i = 0; i < length; ++i) {
        int index = rand() % charset_size;
        printf("%c", charset[index]);
    }
    printf("\n");
}

void parseInput(char *input) {
    // Tokenization
    char *token = strtok(input, " \n"); // Break input into tokens separated by space or newline

    // First token is the command
    char *command = token;

    // Subsequent tokens are arguments
    while (token != NULL) {
        token = strtok(NULL, " \n"); // Get next token

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
                break;  // to avoid redundant else print function
            } else {
                printf("Usage: wc [-l] [-w] [-c] <filename>\n");
            }
        } else if (strcmp(command, "grep") == 0) {
            char *pattern = token;
            token = strtok(NULL, " \n");
            if (token != NULL) {
                char *fileName = token;
                grep(pattern, fileName);
                break;  // to avoid redundant else print function
            } else {
                printf("Usage: grep <pattern> <filename>\n");
            }
        } else if (strcmp(command, "cmatrix") == 0){
            cmatrix();
        } else if (strcmp(command, "df") == 0){
            df("/");
        } else if (strcmp(command, "tiger") == 0){
            tiger();
        } else if (strcmp(command, "pokemon") == 0){
            pokemon();
        } else if (strcmp(command, "thirsty") == 0){
            thirsty();
        } else if (strcmp(command, "pwgen") == 0){
            int length;
            if(token != NULL){
                if(atoi(token)){
                    length = atoi(token);
                    pwgen(length);
                    break;  // to avoid redundant else print function
                } else{
                    printf("You have to enter a integer as a password length!\n");
                }
            } else {
                printf("Usage: pwgen <length>\n");
            }
        } else if (strcmp(command, "help") == 0){
            help();
        } else if (strcmp(command, "ls") == 0) {
            // If the command is "ls", pass the token (directory path) to the ls function
            if (token != NULL) {
                ls(token); // Call ls function with the directory path
                break;
            } else {
                // If no directory path is provided, list the contents of the current directory
                ls("."); // Or any default directory you prefer
            }
        } else {
            printf("Command not found: %s\n", command);
        }
    }
}

int main() {

    while(1){
        char input[200];
        prompt();
        fgets(input, sizeof(input), stdin);
        handleOutputRedirection(input);
        // Fork to execute command
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            parseInput(input);
            exit(EXIT_SUCCESS); // Exit child process
        } else if (pid < 0) {
            // Fork failed
            perror("fork");
        } else {
            // Parent process
            waitpid(pid, NULL, 0); // Wait for child process to finish
        }

        fflush(stdout);
    }
    return 0;
}

