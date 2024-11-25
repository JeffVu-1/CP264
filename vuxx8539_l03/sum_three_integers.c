/**
 * -------------------------------------
 * @file  functions.c
 * Lab 2 Functions Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#include "functions.h"

int sum_three_integers(void) {
	int total = 0;
	int argOne;
	int argTwo;
	int argThree;

    while (1){
		printf("Enter three comma-separated integers: ");
		int filled = scanf("%d,%d,%d", &argOne, &argTwo, &argThree);

		if (filled == 3){
			total = argOne + argTwo + argThree;
			return total;
		}else{
			printf("The integers were not properly entered. \n");
			while (getchar() != '\n');
		}
    }

}
