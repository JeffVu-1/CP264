/**
 * -------------------------------------
 * @file  date.h
 * date Type Header File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#ifndef INT_H_
#define INT_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define INT_STRING_SIZE 11

// Type Definitions
/**
 * date structure.
 *
 * Redefine an existing date type. Examples:
 * typedef float int;
 * typedef food_struct int;
 * typedef movie_struct int;
 */

// Prototypes
/**
 * Deep copies date from source to target.
 * Memory must already be allocated to target.
 *
 * @param target - pointer to copy to.
 * @param source - pointer to copy from.
 */
void int_copy(int *target, const int *source);

/**
 * Compare two date objects.
 *
 * @param target - pointer to date object
 * @param source - pointer to date object
 * @return - 0 if date is the same, < 0 if source < target, > 0 if source > target
 */
int int_compare(const int *target, const int *source);

/**
 * Allocates memory and date to a int item.
 *
 * @param source- pointer to source date
 */
int* int_initialize(int year, int month, int day);

/**
 * Frees complete contents of source.
 *
 * @param source- pointer to source date
 */
void int_destroy(int **source);

/**
 * Returns string version of date object.
 *
 * @param string - destination string
 * @param size - maximum size of destination string
 * @param source - pointer to source date
 * @return pointer to string
 */
char* int_string(char string[], size_t size, const int *source);

#endif /* INT_H_ */
