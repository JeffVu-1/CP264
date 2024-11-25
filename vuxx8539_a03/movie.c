/**
 * -------------------------------------
 * @file  movie.c
 * movie Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#include "movie.h"

// Array of strings for movie genres.
const char *const GENRES[] = {"science fiction", "fantasy", "drama", "romance", "comedy", "zombie", "action",
        "historical", "horror", "war", "mystery"};

// Calculates size of GENRES array.
const int GENRES_COUNT = sizeof GENRES / sizeof *GENRES;

void movie_init(movie_struct *source, const char *title, int year, const char *director, int genre, float rating) {
    assert(year >= FIRST_YEAR);
    assert(rating >= MIN_RATING && rating <= MAX_RATING);

    strncpy(source->title, title, MAX_STRING - 1);
    strncpy(source->director, director, MAX_STRING - 1);
    source->year  = year;
    source->genre = genre;
    source->rating = rating;
}

void movie_copy(const movie_struct *source, movie_struct *target) {
    strncpy(target->title, source->title, sizeof(target->title) - 1);
    target->title[sizeof(target->title) - 1] = '\0';


    strncpy(target->director, source->director, sizeof(target->director) - 1);
    target->director[sizeof(target->director) - 1] = '\0';

    target->year = source->year;
    target->genre = source->genre;
    target->rating = source->rating;
}


int movie_compare(const movie_struct *source, const movie_struct *target) {

	int result = strcmp(source->title, target->title);

	if (result == 0){
		if (source->year == target->year){
			return 0;
		} else if(source->year < target->year){
			return -1;
		}else{
			return 1;
		}
	} else if (result < 0) {
       return -1;
    } else {
        return 1;
    }

}

void movie_print(const movie_struct *source) {

    printf("Title:    %s\n", source->title);
    printf("Year:     %d\n", source->year);
    printf("Director: %s\n", source->director);
    printf("Genre:    %s\n", GENRES[source->genre]);
    printf("Rating:   %.1f\n", source->rating);
}

char* movie_key(char *str, size_t max_length, movie_struct *source) {
	snprintf(str, max_length, "%s: %d", source->title, source->year);
	return str;
}

void genres_menu() {
	printf("Genres\n");
    for (int i = 0; i < GENRES_COUNT; ++i){
    	printf("%2d: %s\n", i, GENRES[i]);
    }

}
