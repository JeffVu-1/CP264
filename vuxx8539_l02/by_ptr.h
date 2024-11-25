/**
 * -------------------------------------
 * @file  by_ptr.h
 * Lab 2 Pointer Functions Header File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BY_PTR_H_
#define BY_PTR_H_

// Prototypes.

/**
 * Populates values with consecutive integers in the range [1 to size].
 * Uses pointer arithmetic.
 *
 * @param values - array of int
 * @param size - size of values
 */
void fill_values_by_ptr(int *values, int size);

/**
 * Populates squares with the squares of the corresponding integers in values.
 * Uses pointer arithmetic.
 *
 * @param values - array of int
 * @param squares - array of int, each a square of corresponding int in values
 * @param size - size of values and squares
 */
void fill_squares_by_ptr(int *values, long int *squares, int size);

/**
 * Prints the contents of values and squares in two columns.
 * Uses pointer arithmetic.
 *
 * @param values - array of int
 * @param squares - array of int, each a square of corresponding int in values
 * @param size - size of values and squares
 */
void print_by_ptr(int *values, long int *squares, int size);

#endif /* BY_PTR_H_ */
