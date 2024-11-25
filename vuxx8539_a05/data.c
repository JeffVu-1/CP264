/**
 * -------------------------------------
 * @file  data.c
 * Data Type Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
// Includes
#include <stdio.h>

#include "data.h"

// Functions

char* data_string(char *string, size_t size, data_ptr data) {
    snprintf(string, size, "%d", *data);
    return string;
}

void data_copy(data_ptr target, const data_ptr source) {
    *target = *source;
}

int data_compare(const data_ptr source, const data_ptr target) {
    int result = 0;

    if(*source < *target) {
        result = -1;
    } else if(*source > *target) {
        result = 1;
    }
    return (result);
}

void data_free(data_ptr *source) {
    free(*source);
    *source = NULL;
    return;
}
