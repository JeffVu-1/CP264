/**
 * -------------------------------------
 * @file  int_data.h
 * int_data Header File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#ifndef INT_DATA_
#define INT_DATA_

#include <stdio.h>
#include <stdlib.h>

/**
 * Data structure.
 */
typedef int data_type;

// Prototypes

/**
 * Copies source integer to target integer.
 *
 * @param target - pointer to target.
 * @param source - pointer to source.
 * @return - pointer to source
 */
void int_copy(const int *source, int *target);

/**
 * Prints an integer.
 *
 * @param source - pointer to an integer.
 */
void int_print(const int *source);

/**
 * Compares two integers. Movies are compared first by title, then by year.
 *
 * @param source - pointer to int.
 * @param target - pointer to int.
 * @return - 0 if source == target, < 0 if source < target, > 0 if source > target.
 */
int int_compare(const int *source, const int *target);

#endif /* INT_DATA_ */
