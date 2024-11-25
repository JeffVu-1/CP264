/**
 * -------------------------------------
 * @file  pq_dynamic.c
 * Dynamic Priority Queue Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#include "pq_dynamic.h"

// Functions

// Initializes a priority queue.
void pq_initialize(pq_dynamic_struct** source, int capacity) {
    *source = malloc(sizeof(pq_dynamic_struct));
    (*source)->capacity = capacity;
    (*source)->count = 0;
    (*source)->first = -1;
    (*source)->items = malloc(capacity * sizeof(data_type)); 
}

// Destroys a priority queue.
void pq_destroy(pq_dynamic_struct **source) {
    free((*source)->items);
    (*source)->items = NULL;
    free(*source);
    (*source) = NULL;
}

// Determines if a priority queue is empty.
bool pq_empty(const pq_dynamic_struct *source) {
    return (source->count == 0);
}

// Determines if the queue is full.
bool pq_full(const pq_dynamic_struct* source) {
    return (source->count >= source->capacity);
}

// Returns the number of items in the queue.
int pq_count(const pq_dynamic_struct *source) {
    return (source->count);
}

// Inserts an item into a priority queue.
bool pq_insert(pq_dynamic_struct *source, data_type *item) {
    //we have to check if it's full and add more spots
    if (pq_full(source)){
        source->capacity *= 2;
        data_type* ptr = realloc(source->items, source->capacity * sizeof source->items);
        assert(ptr != NULL);
        source->items = ptr;
    }

    if (source->first == -1) {
        source->first = 0; 
        source->items[source->first] = *item; 
        source->count++;
        return 1;
    }
    
    int index;
    for (index = source->count - 1; index >= 0; index--) {
        if (*item < source->items[index]) {
            source->items[index + 1] = source->items[index];
        }
        else {
            break;
        }
    }
    source->items[index + 1] = *item;
    source->count++;
    return 1;
}
  
// Returns a copy of the first of a priority queue.
bool pq_peek(const pq_dynamic_struct *source, data_type *item) {
    if (pq_empty(source)) {
        return 0;
    }

    *item = source->items[source->first];
	return 1;
}

// Returns and removes the item on the first of a priority queue.
bool pq_remove(pq_dynamic_struct *source, data_type *item) {
    if (pq_empty(source)) {
        return 0;
    }

    *item = source->items[source->first];
    for (int i = source->first; i < source->count - 1; i++) {
        source->items[i] = source->items[i + 1];
    }

    source->count--;

    if (source->count == 0) {
        source->first = -1;
    }
    else {
        source->first = 0; 
    }
   
	return 1;
}

// Prints the items in a priority queue from first to rear.
void pq_print(const pq_dynamic_struct *source) {
    // Walk through stack from top to bottom using indexes.
    for(int i = 0; i < source->count; i++) {
        data_print(&(source->items[i]));
        printf("\n");
    }
    return;
}
