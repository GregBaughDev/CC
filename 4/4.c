#include "4.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

// 2: allow user to set the delim char

int main(int argc, char *argv[]) {
    int     opt;
    char    *fieldOpt = NULL;
    char    *delimOpt = NULL;
    char    *fileName;
    int     argFilePos = 3;
    FILE    *inputFile;
    struct  stat fileInfo;
    char    *buffer;

    if (argc < 3) {
        printf("Usage: -f1,2 filename");
        exit(EXIT_FAILURE);
    }

    while ((opt = getopt(argc, argv, OPTSTR)) != -1) {
        switch (opt) {
            case 'f':
                fieldOpt = optarg;
                printf("fieldOpt %s\n", fieldOpt);
                break;
            case 'd':
                delimOpt = optarg;
                printf("delimOpt %s\n", delimOpt);
            default:
                break;
        }
    }
    // curr state: 
    // need to do the part where we stop hardcoding tabchar and tempoptarg
    
    if (delimOpt == NULL) { // test w/out make
        delimOpt = "\t";
        argFilePos = 2;
    }

    fileName = malloc(strlen(argv[argFilePos]));
    if (fileName == NULL) {
        puts("Unable to allocate memory for fileName");
        exit(EXIT_FAILURE);
    }
    fileName = argv[argFilePos];

    if (!(inputFile = fopen(fileName, "r"))) {
        perror(ERR_FOPEN_INPUT);
        exit(EXIT_FAILURE);
    }
    
    if (stat(fileName, &fileInfo) < 0) {
        exit(EXIT_FAILURE);
    }

    buffer = malloc(fileInfo.st_size);
    if (buffer == NULL) {
        puts("Unable to allocate buffer memory");
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, fileInfo.st_size, inputFile); // need to handle this for error/eof
    fclose(inputFile);

    int tempOptarg = 2; // replace this with optarg - will also need to handle gtr than fields error
    int tabChar = 1;
    char *concatString = NULL;
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == TAB) {
            tabChar++;
            continue;
        }

        if (buffer[i] == NEWLINE) {
            puts(concatString);
            tabChar = 1;
            if ((realloc(concatString, 1)) == NULL) {
                puts("concatString realloc failed");
                exit(EXIT_FAILURE);
            }
            concatString = NULL;
            continue;
        }

        if (i == strlen(buffer) - 1) {
            puts(concatString);
            break;
        }

        if (tabChar == tempOptarg) {
            if (concatString == NULL) {
                concatString = malloc(2);
            } else {
                concatString = realloc(concatString, strlen(concatString) + 1);
            }
            if (concatString == NULL)  {
                puts("concatString realloc failed");
                exit(EXIT_FAILURE);
            }
            concatString[strlen(concatString)] = buffer[i];
            concatString[strlen(concatString) + 1] = '\0';
        }
    }

    free(concatString);
    free(buffer);

    printf("Made it this far without a seg fault!\n");
    return 0;
}