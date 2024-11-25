/**
 * -------------------------------------
 * @file  main.c
 * Assignment 1 Main Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);

	printf("Converted From Feet to Acres: %.2f\n", feet_to_acres((100000)));
	printf("How long it takes to mow a rectangular lawn: %d\n", mow_lawn(10.0, 10.0, 5.0));
	printf("Converted from DDMMYYYY to YYYYMMDD: %d\n", date_convert(25101962));
	printf("Time it took for object to fall: %d\n", falling_time(50));
	printf("Calculated hypotenuse Value: %.1f\n", hypotenuse(3.0, 4.0));
	printf("Sum Even: %d\n", sum_even(100));
	printf("Sum Partial: %f\n", sum_partial_harmonic(4));
	printf("Population Growth: %d\n", population_growth(10, 10.0, 100));

	return 0;
}
