/**
 * -------------------------------------
 * @file  int_data.c
 * int_data Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
// Includes
#include "int_data.h"

// Functions

void int_copy(const int *source, int *target) {
    *target = *source;
}

void int_print(const int *source) {
    printf("%d", *source);
}

int int_compare(const int *source, const int *target) {
    int result = 0;

    if(*source < *target) {
        result = -1;
    } else if(*source > *target) {
        result = 1;
    }
    return (result);
}
