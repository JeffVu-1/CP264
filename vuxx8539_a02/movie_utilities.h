/**
 * -------------------------------------
 * @file  movie_utilities.h
 * Assignment 2 movie_utilities Header File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#ifndef MOVIE_UTILITIES_H_
#define MOVIE_UTILITIES_H_

#include "movie.h"

/**
 * Initializes a movie structure from a line of formatted string data.
 *
 * @param source - pointer to a movie structure
 * @param line - delimited string of movie data.
 */
void read_movie(movie_struct *source, const char *line);

/**
 * Reads a movie object from the keyboard.
 *
 * @param source - pointer to a movie structure
 */
void get_movie(movie_struct *source);

#endif /* MOVIE_UTILITIES_H_ */
