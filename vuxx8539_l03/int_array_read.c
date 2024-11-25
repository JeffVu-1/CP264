/**
 * -------------------------------------
 * @file  int_array_read.c
 * Lab 3 Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#include "functions.h"

void int_array_read(int *array, int size) {

    printf("Enter 4 values for an array of int.\n");
    for (int i = 0; i < size; ++i){
    	int number;
    	while (1){
    		printf("Value for index %d: ", i);
			if(scanf("%d", &number) == 1){
				*(array + i) = number;
				break;
			}else{
				printf("Not a valid integer\n");
			    while (getchar() != '\n');
			}
    	}
    }
}
