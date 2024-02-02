#include "4.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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