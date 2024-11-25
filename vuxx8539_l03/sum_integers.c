/**
 * -------------------------------------
 * @file  sum_integers.c
 * Lab 3 Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#include "functions.h"

int sum_integers(void) {

	int total;
	printf("Enter integers, one per line: \n");

	while (1){
		int number;

		if (scanf("%d", &number) == 1) {
			total += number;
		}
		else {
			break;
		}
	}

	return total;
}
