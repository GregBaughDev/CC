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
    char    *buffer;
    // curr state
    // next time - print second field from -f2 from sample.tsv

    if (argc < 3) {
        printf("Usage: -f1,2 filename");
        exit(EXIT_FAILURE);
    }

    opt = getopt(argc, argv, OPTSTR); // optarg gives us the opt
    printf("%s is %lu length\n", argv[2], strlen(argv[2] + 1));

    fileName = malloc(strlen(argv[2]));
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

    buffer = malloc(1 * fileInfo.st_size);
    if (buffer == NULL) {
        printf("Unable to allocate buffer memory");
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, fileInfo.st_size, inputFile);
    printf("buffer:\n%s\n", buffer);

    // could use a int var which compares agains the optarg
    // reset it each time we hit newline
    // increase intvar when we hit tabchar
    // concat the string until you reach a tab char
    // add the string to a results buffer
    // realloc the size of the results buffer each time we add the concat string

    int tabChar = 0;
    char concat[] = "";
    for (int i = 0; i < strlen(buffer); i++) {
        printf("%i: %i\n", i, (int) buffer[i]);
    }

    printf("Made it this far without a seg fault!\n");

    free(buffer);
    fclose(inputFile);

    return 0;
}