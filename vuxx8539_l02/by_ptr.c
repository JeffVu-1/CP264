/**
 * -------------------------------------
 * @file  by_ptr.c
 * Lab 2 Pointer Functions Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#include "by_ptr.h"

void fill_values_by_ptr(int *values, int size) {

    for(int i = 0; i < size; i++) {
        *(values + i) = i + 1;
    }
}

void fill_squares_by_ptr(int *values, long int *squares, int size) {

    for (int i = 0; i < size; ++i){
    	*(squares + i) = (*(values + i)) * (*(values + i));
    }
}

void print_by_ptr(int *values, long int *squares, int size) {

    printf("Value  Square\n");
    printf("-----  ----------\n");
    for (int i = 0; i < size; ++i){
    	printf("%5d%12d\n", *(values + i), *(squares + i));
    }
}
