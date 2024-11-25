/**
 * -------------------------------------
 * @file  queue_dynamic.c
 * Dynamic Queue Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 2024-10-05
 *
 * -------------------------------------
 */
#include "queue_dynamic.h"

// Functions

// Initializes a queue.
void queue_initialize(queue_dynamic_struct **source, int capacity) {
    (*source) = malloc(sizeof(queue_dynamic_struct));
    (*source)->capacity = capacity;
    (*source)->count = 0;
    (*source)->front = 0;
    (*source)->rear = 0;
    (*source)->items = malloc(capacity * sizeof(data_type));
}

// Destroys a queue.
void queue_destroy(queue_dynamic_struct **source) {
    free((*source)->items);
    (*source)->items = NULL;
    free(*source);
    (*source) = NULL;
}

// Determines if a queue is empty.
bool queue_empty(const queue_dynamic_struct *source) {
    return (source->count == 0);
}

// Determines if the queue is full.
bool queue_full(const queue_dynamic_struct *source) {
    return (source->count >= source->capacity);
}

// Returns the number of items in the queue.
int queue_count(const queue_dynamic_struct *source) {
    return source->count;
}

// Inserts an item into a queue.
bool queue_insert(queue_dynamic_struct *source, data_type *item) {
    if (queue_full(source)) {
        source->capacity *= 2;
        data_type* ptr = realloc(source->items, source->capacity * sizeof(data_type));
        assert(ptr != NULL);
        source->items = ptr;
    }

    source->items[source->count] = *item;
    source->count++;

    return 1;
}

// Returns a copy of the front of a queue.
bool queue_peek(const queue_dynamic_struct *source, data_type *item) {
    if (queue_empty(source)) {
        return 0;
    }
    *item = source->items[source->front];
	return 1;
}

// Returns and removes the item on the front of a queue.
bool queue_remove(queue_dynamic_struct* source, data_type* item) {
    if (queue_empty(source)) {
        return 0; 
    }
    *item = source->items[source->front];

    source->front++;
    source->count--;

    if (source->count == 0) {
        source->front = 0; 
        source->rear = 0; 
    }

    return 1; 
}

void queue_print(const queue_dynamic_struct *source) {
    // Walk through queue from front to rear using indexes.
    int temp = source->front;

    for(int i = 0; i < source->count; i++) {
        data_print(&(source->items[temp]));
        printf("\n");
        temp = (temp + 1) % source->capacity;
    }
    return;
}
