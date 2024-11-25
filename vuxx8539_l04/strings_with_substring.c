/**
 * -------------------------------------
 * @file  strings_with_substring.c
 * Lab 4 Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#include "functions.h"

void strings_with_substring(strings_array *data, char *substr) {

	for (int i = 0; i < data->lines; ++i){
		char *current_string = data->strings[i];
		if (current_string != NULL &&strstr(current_string, substr) != NULL){
			printf("%s\n", current_string);
		}
	}


}
