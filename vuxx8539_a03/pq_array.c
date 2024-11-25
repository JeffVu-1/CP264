/**
 * -------------------------------------
 * @file  pq_array.c
 * pq_array Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#include "pq_array.h"

// Functions

/**
 * Initializes a priority queue.
 *
 * @param source - the priority queue to initialize.
 */
void pq_initialize(pq_struct *source){
	source->capacity = PQ_INIT;
	source->count = 0;
	source->first = 0;
    return;
}

/**
 * Determines if a priority queue is empty.
 *
 * @param source - pointer to a priority queue.
 * @return - true if a priority queue is empty, false otherwise.
 */
bool pq_empty(const pq_struct *source){
    return source->count == 0;
}

/**
 * Determines if a priority queue is full.
 *
 * @param source - pointer to a priority queue.
 * @return - true if a priority queue is full, false otherwise.
 */
bool pq_full(const pq_struct *source){
    return source->count == source->capacity;
}

/**
 * Returns the number of items in a priority queue.
 *
 * @param source - pointer to a priority queue.
 * @return - the number of items in a priority queue.
 */
int pq_count(const pq_struct *source){
    return source->count;
}

/**
 * Inserts an item into a priority queue.
 *
 * @param source - pointer to a priority queue.
 * @param item - the item to insert.
 * @return - true if item inserted, false otherwise (pq is full)
 */
bool pq_insert(pq_struct *source, data_type *item) {
    if (pq_full(source)) { // check if it's full as then we can't insert
        return 0;
    }


    int i;
    //travse backwards so it's easier
    for (i = source->count - 1; i >= 0; --i) {
        if (*item < source->items[i]) {
            source->items[i + 1] = source->items[i];
        } else {
            break;
        }
    }
    // we need to add 1 because it's holding the position previous
    // so for instance it's at 0 2 3 4 5 but we have to insert it after 0

    source->items[i + 1] = *item;
    //then of course increase this
    source->count++;

    return 1;
}

/**
 * Returns a copy of the highest priority item in a priority queue.
 *
 * @param source - pointer to a priority queue.
 * @param item - the item to peek.
 * @return - true if item peeked, false otherwise (pq is empty)
 */
bool pq_peek(const pq_struct *source, data_type *item){
	if (pq_empty(source)){
		return 0;
	}
	*item = source->items[source->first];
    return 1;
}

/**
 * Returns and removes the item on the front of a priority queue.
 *
 * @param source - pointer to a priority queue.
 * @param item - the item to peek.
 * @return - true if item removed, false otherwise (pq is empty)
 */
bool pq_remove(pq_struct *source, data_type *item) {
    if (pq_empty(source)) {
        return 0;
    }

    *item = source->items[source->first];
    source->count--;

    if (source->count > 0) {
        source->items[source->first] = source->items[source->count];
    } else {
        source->first = 0;
    }

    return 1;
}



/**
 * Prints the items in a priority queue from front to rear.
 * (For testing only).
 *
 * @param source - pointer to a priority queue
 */
void pq_print(const pq_struct *source){
	if (pq_empty(source)){
		printf("Empty");
	}else{
		printf("Items in PQ:\n");
		for (int i = 0; i < source->count; ++i) {
			printf("%d\n", source->items[i]);
		}
	}
    return;
}
