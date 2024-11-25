/**
 * -------------------------------------
 * @file  strings_length.c
 * Lab 4 Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#include "functions.h"

void strings_length(strings_array *data, FILE *fp_short, FILE *fp_long, int length) {

	for (int i = 0; i < data->lines; ++i){
		char *current_string = data->strings[i];

		if (current_string != NULL){
			int string_length = strlen(current_string);

			if (string_length < length){
				fprintf(fp_short, "%s\n", current_string);
			}else{
				fprintf(fp_long, "%s\n", current_string);
			}
		}
	}

}
