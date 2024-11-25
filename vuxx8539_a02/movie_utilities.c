/**
 * -------------------------------------
 * @file  movie_utilities.c
 * Assignment 2 movie_utilities Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#include "movie_utilities.h"

	void get_movie(movie_struct *source) {

		printf("Title: ");
		scanf("%[^\n]", source->title);

		printf("Year: ");
		scanf("%d", &source->year);

		printf("Director: ");
		scanf(" %[^\n]", source->director);

		genres_menu();

		printf("Genre: ");
		scanf("%d", &source->genre);

		printf("Rating: ");
		scanf("%f", &source->rating);
	}

	void read_movie(movie_struct *source, const char *line) {
	    sscanf(line, "%99[^|]|%d|%99[^|]|%f|%d", source->title, &source->year, source->director, &source->rating, &source->genre);
	}
