#include "4.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

// 3: allow list of fields to be passed in
// now just need to not print the last delim char!

// additional todos:
// loop over the fields to check number of fields is < 0 && == fieldNum

int fieldsToArray(char *fields, int *array) {
    int arrPos = 0;
    for (int i = 0; i < strlen(fields); i++) {
        int fieldChar = (int) fields[i];
        if (fieldChar >= 48 && fieldChar <= 57) {
            array[arrPos] = (int) strtol(&fields[i], NULL, 10);
            arrPos++;
        }
    }
    return arrPos;
}

int main(int argc, char *argv[]) {
    int     opt;
    // deprecate the below
    char    *fieldOpt = NULL;
    // maybe dynamically do the array
    int     fieldArr[5];
    int     fieldArrLen;    
    int     delimOpt = TAB;
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
                fieldArrLen = fieldsToArray(optarg, fieldArr);
                break;
            case 'd':
                delimOpt = (int) optarg[0];
            default:
                break;
        }
    }
    // curr state: 
    // should start splitting things into fn's
    
    if (argc == 3) { // test w/out make
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

    int argChar = 1;
    char *concatString = NULL;
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == NEWLINE) {
            puts(concatString);
            argChar = 1;
            if ((realloc(concatString, 1)) == NULL) {
                puts("concatString realloc failed");
                exit(EXIT_FAILURE);
            }
            concatString = NULL;
            continue;
        }

        for (int j = 0; j < fieldArrLen; j++) {
            if (argChar == fieldArr[j]) {
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

        if (buffer[i] == delimOpt) {
            argChar++;
            continue;
        }

        if (i == strlen(buffer) - 1) {
            puts(concatString);
            break;
        }
    }

    free(concatString);
    free(buffer);

    printf("Made it this far without a seg fault!\n");
    return 0;
}