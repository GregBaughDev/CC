#include "4.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

// 1: open the provided tab separated file and print out
// the second field from each line
// will need -> field value, file name from stdin
// 1a. let's print the file to stdout first off

int main(int argc, char *argv[]) {
    int     opt;
    char    *fileName;
    FILE    *inputFile;
    struct  stat fileInfo;
    // curr state
    // use fileSize to allocate space in buffer for file content

    opt = getopt(argc, argv, OPTSTR); // optarg gives us the opt
    printf("%s is %lu length\n,", argv[2], strlen(argv[2] + 1));

    fileName = (char *) malloc(strlen(argv[2]));
    if (fileName == NULL) {
        printf("Unable to allocate memory for fileName");
        exit(EXIT_FAILURE);
    }

    fileName = argv[2];

    if (!(inputFile = fopen(fileName, "r"))) {
        perror(ERR_FOPEN_INPUT);
        exit(EXIT_FAILURE);
    }
    
    if (stat(fileName, &fileInfo) < 0) {
        exit(EXIT_FAILURE);
    }

    printf("opt is: %c and that is %s\n", opt, optarg);
    printf("file is: %i bytes", fileInfo.st_size);

    for (int i = 0; i < argc; i++) {
        printf("Arg: %d, %s\n", i, *(argv + i));
    }

    return 0;
}