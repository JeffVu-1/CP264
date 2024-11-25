/**
 * -------------------------------------
 * @file  functions.c
 * Assignment 1 Functions Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */

#include "functions.h"


double feet_to_acres(int square_feet) {
	return (square_feet / FEET_PER_ACRE);
}

int mow_lawn (double width, double length, double speed ) {
	return ((width * length) / speed);
}


int date_convert(int date_number){
	int DD = date_number / 1000000;
	int MM = (date_number / 10000) % 100;
	int YYYY = date_number % 10000;
	return YYYY * 10000 + MM * 100 + DD;
}

int falling_time(int distance) {
	return sqrt(2 * distance / GRAVITY_ACCEL);
}

double hypotenuse(double x, double y) {
	return sqrt(((x * x) + (y * y)));
}

int sum_even(int n) {

	int total;

	for (int i = 2; i <= n; ++i) {

		if (i % 2 == 0) {
			total += i;
		}
	}

	return total;
}

double sum_partial_harmonic(int n) {

	float total;

	for (int i = 1; i <= n; ++i) {
		total += 1.0 / i;
	}

	return total;
}


int population_growth(int start, double rate, int target) {
    rate = rate / 100.0;
    double t = log((double)target / start) / rate;
    return (int)ceil(t);
}
