/**
 * -------------------------------------
 * @file  min_heap.c
 * Minimum Heap Source Code File
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
#include "min_heap.h"

#define STRING_SIZE 80

// local functions

/**
 * Swaps two data values.
 *
 * @param a pointer to data.
 * @param b pointer to data.
 */
static void heap_swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

/**
 * Moves the last value in source until it is in its correct location
 * in source.
 *
 * @param source - pointer to a heap
 */
static void heapify_up(min_heap *source) {
    if (source == NULL) {
        return;
    }

    int LastItemInsertedIndex = source->count - 1;

    while (LastItemInsertedIndex > 0) {
        int parent_index = (LastItemInsertedIndex - 1) / 2;
        if (source->values[LastItemInsertedIndex] < source->values[parent_index]) {
            heap_swap(&source->values[LastItemInsertedIndex], &source->values[parent_index]);
            LastItemInsertedIndex = parent_index;
        } else {
            break;
        }
    }
}

/**
 * Moves a value down source to its correct position.
 *
 * @param source - pointer to a heap
 */
static void heapify_down(min_heap *source) {
    if (source == NULL) {
        return;
    }

    int index = 0;

    while (index < source->count) {
        int IndexLeftChild = (index * 2) + 1;
        int IndexRightChild = (index * 2) + 2;
        int smallest_index = index;

        if (IndexLeftChild < source->count && source->values[IndexLeftChild] < source->values[smallest_index]) {
            smallest_index = IndexLeftChild;
        }

        if (IndexRightChild < source->count && source->values[IndexRightChild] < source->values[smallest_index]) {
            smallest_index = IndexRightChild;
        }

        if (smallest_index != index) {
            heap_swap(&source->values[index], &source->values[smallest_index]);
            index = smallest_index;
        } else {
            break;
        }
    }

    return;
}


// Public minimum heap functions
min_heap* min_heap_initialize(int capacity) {
    min_heap *source = malloc(sizeof *source);
    source->values = malloc(capacity * sizeof *source->values);
    source->capacity = capacity;
    source->count = 0;
    return source;
}

void min_heap_free(min_heap **source) {
    free((*source)->values);
    (*source)->values = NULL;
    free(*source);
    *source = NULL;
    return;
}

void min_heap_heapify(min_heap *source, int *keys, int count) {

    for(int i = 0; i < count; i++) {
        min_heap_insert(source, keys[i]);
    }
    return;
}

int min_heap_empty(const min_heap *source) {
    return (source->count == 0);
}

int min_heap_full(const min_heap *source) {
    return (source->count == source->capacity);
}

int min_heap_count(const min_heap *source) {
    return (source->count);
}

void min_heap_insert(min_heap *source, const int value) {
    // Add new value to end of the heap.
    source->values[source->count] = value;
    source->count++;
    // Fix the heap.
    heapify_up(source);
    return;
}

int min_heap_peek(const min_heap *source) {
    return (source->values[0]);
}

int min_heap_remove(min_heap *source) {
    int value = source->values[0];
    source->count--;

    if(source->count > 0) {
        // Move last value to top of heap.
        source->values[0] = source->values[source->count];
        // Fix the heap.
        heapify_down(source);
    }
    return value;
}

int min_heap_valid(const min_heap *source) {
	if(source == NULL){
		return 0;
	}

	int index = 0;

	while(index < source->count){
		int IndexLeftChild = (index * 2 + 1);
		int IndexRightChild = (index * 2 + 1);
		//check left child first
		if (IndexLeftChild < source->count && source->values[index] > source->values[IndexLeftChild]) {
			return 0;
		}
		//check right childs affters
		if (IndexRightChild < source->count && source->values[index] > source->values[IndexRightChild]) {
			return 0;
		}

		//go next
		index++;
	}

    return 1;
}

int min_heap_replace(min_heap *source, int replacement) {
    int value = source->values[0];
    source->values[0] = replacement;
    heapify_down(source);
    return value;
}

void heap_sort(int *values, int count) {
	for (int i = 0; i < count - 1; i++) { //outerloop loops through size of array
		for (int j = 0; j < count - 1 - i; j++) { // this will loop 1 less each time because biggest number is always last each interation
			if (values[j] > values[j + 1]) { // if the current value is more then the next one then perform the swap
				int temp = values[j];
				values[j] = values[j + 1];
				values[j + 1] = temp;
			}
		}
	}
	return;
}

// for testing
void min_heap_print(const min_heap *source) {
    printf("{");

    for(int i = 0; i < source->count; i++) {
        printf("%d, ", source->values[i]);
    }
    printf("}\n");
    return;
}
