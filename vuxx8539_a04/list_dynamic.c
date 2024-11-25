/**
 * -------------------------------------
 * @file  list_dynamic.c
 * Dynamic List Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#include "list_dynamic.h"

// Private helper functions

/**
 * Determines if an index is valid.
 *
 * @param list - pointer to a list.
 * @param i - index to check
 * @return - true if i is a valid index, false otherwise
 */
static bool valid_index(const list_dynamic_struct *source, int i) {
    return ((i >= 0) && (i <= source->count));
}

/**
 * Performs a linear search on source->items for key.
 *
 * @param list - pointer to a list.
 * @param key - key of item to look for in list.
 * @return - index of location of key in list, -1 if key not in list.
 */
static int list_linear_search(const list_dynamic_struct *source, const data_type *key) {

	int index;
    for (int i = 0; i < source->count; ++i){
    	if ((*key) == source->items[i]){
    		index = i;
    		printf("Found a Key!!!!!!");
    		break;
    	}
    }
    return index;
}

// Functions


//typedef struct {
//    int capacity;               // capacity of the list.
//    int count;                  // count of items in list.
//    data_type *items;		           	// array of data items.
//} list_dynamic_struct;

// Initializes a list.
void list_initialize(list_dynamic_struct **source, int capacity) {
    *source = malloc(sizeof(list_dynamic_struct));
    (*source)->capacity = capacity;
    (*source)->count = 0;
    (*source)->items = malloc(capacity * sizeof(*source)->items);
}

// Destroys a list.
void list_destroy(list_dynamic_struct **source) {
	free((*source)->items);
	(*source)->items = NULL;
	free(*source);
	*source = NULL;
}

// Determines if a list is empty.
bool list_empty(const list_dynamic_struct *source) {
	return (source->count == 0 ? 1: 0);
}

// Determines if the list is full.
bool list_full(const list_dynamic_struct *source) {
    return ((source->count == source->capacity));
}

// Appends a item to the end of a list.
bool list_append(list_dynamic_struct *source, data_type *item) {

	if (list_full(source)){
		//now we need to append more space for it
		source->capacity *= 2;
		data_type *ptr = realloc(source->items, source->capacity * sizeof(source->items));
		source->items = ptr;
	}

	//now either it now has more space or it had space we need to append

	//append the item to the end of the list but we also have to check it if it's full first
	source->items[source->count] = *item;
	source->count++;
	return 1;
}

// Returns the number of items in the list.
int list_count(const list_dynamic_struct *source) {
	return source->count;
}

// Inserts a item to a list at location i.
bool list_insert(list_dynamic_struct *source, data_type *item, int i) {


	// we have to check if the index we are trying to insert exceeds the capacity
	//beacuse if it does then we havea to increase until we reach it...

	if (i < 0 || i > source->count) {
	        return false;  // Index out of bounds
	    }

	if (list_full(source)) {
		// Double the capacity
		int new_capacity = source->capacity * 2;
		data_type *new_items = realloc(source->items, new_capacity * sizeof(data_type));
		if (new_items == NULL) {
			return false;  // Memory allocation failed
		}
		source->items = new_items;
		source->capacity = new_capacity;
	}

	for (int k = source->count; k > i; k--) {
	        source->items[k] = source->items[k - 1];
	    }

	source->items[i] = *item;

    source->count++;

    return 1;
}

// Returns a copy of the front of a list.
bool list_peek(const list_dynamic_struct *source, data_type *item) {
	if(list_empty(source)){
		return 0;
	}

	//if the list isn't empty we have to update the top value
    *item = source->items[0];
    return 1;
}

// Returns a copy of the item matching key in a list.
bool list_key_find(const list_dynamic_struct *source, const data_type *key, data_type *item) {
	if(list_empty(source)){
		return 0;
	}

	for(int i = 0; i < source->count; ++i){
		if ((*key) == source->items[i]){
			*item = source->items[i];
			return 1;
		}
	}

	return 0;
}

// Removes and returns the item matching key from the list.
bool list_key_remove(list_dynamic_struct *source, const data_type *key, data_type *item) {
	if (list_empty(source)){
		return 0;
	}

	int FoundIndex = list_key_index(source, key);
	if (FoundIndex != -1){
		//Since it is found we return a copy

		list_index_remove(source, item, FoundIndex);

		return 1;
	}

	//if it returns -1 from the list_key_index function then return false
	return 0;
}

// Returns the index of key in list. -1 if key not in list.
int list_key_index(const list_dynamic_struct *source, const data_type *key) {
	if (list_empty(source)){
		return -1;
	}

	int FoundIndex;
	for (int i = 0; i < source->count; ++i){
		if (*key == source->items[i]){
			FoundIndex = i;
			break;
		}else{
			FoundIndex = -1;
		}
	}

	return FoundIndex;
}

// Determines if key is in a list.
bool list_key_contains(const list_dynamic_struct *source, const data_type *key) {
	if (list_empty(source)) {
		return 0;
	}

	for (int i = 0; i < source->count; ++i) {
		if (*key == source->items[i]) {
			return 1;
		}
	}

    return 0;
}

// Determines number of times key appears in list.
int list_key_count(const list_dynamic_struct *source, const data_type *key) {
	if (list_empty(source)) {
		return 0;
	}
	
	int count = 0;
	for (int i = 0; i < source->count; ++i) {
		if (*key == source->items[i]) {
			count++;
		}
	}

	return count;
}

// Removes and returns the item at index i from a list.
bool list_index_remove(list_dynamic_struct *source, data_type *item, int i) {
	if (i < 0 || i > source->count) {
		return 0;
	}

	if (list_empty(source)) {
		return 0;
	}

	//give them the item
	*item = source->items[i];

	//now we have to update the list
	for (int jj = i; jj < source->count - 1; jj++) {
		source->items[jj] = source->items[jj + 1];
	}

	source->count--;
	
	return 1;
}

// Finds the maximum item in a list.
bool list_max(const list_dynamic_struct *source, data_type *item) {
	if (list_empty(source)){
		return 0;
	}
	int max = source->items[0];

	for(int i = 0; i < source->count; ++i){
		if(max < source->items[i]){
			max = source->items[i];
		}
	}

	*item = max;
	return 1;
}

// Finds the minimum item in a list.
bool list_min(const list_dynamic_struct *source, data_type *item) {
	if(list_empty(source)){
		return 0;
	}
	int min = source->items[0];
	for (int i = 0; i < source->count; ++i){
		if (min > source->items[i]){
			min = source->items[i];
		}
	}

	*item = min;
	return 1;
}

// Removes all duplicate items from a list.
void list_clean(list_dynamic_struct* source) {

	for (int i = 0; i < source->count; i++) {
		for (int j = i + 1; j < source->count; j++) {
			if (data_compare(&(source->items[i]), &(source->items[j])) == 0) {
				//we need to shift the items over here to fill in the gaps
				for (int k = j; k < source->count - 1; k++) {
					source->items[k] = source->items[k + 1];
				}
				source->count--;
				j--;
			}
		}
	}
}


// Compares two lists for equality.
bool list_equal(const list_dynamic_struct *target, const list_dynamic_struct *source) {
	//if they're both empty then return true
	if (list_empty(target) && list_empty(source)) {
		return 1;
	}

	//now if they're both not empty then check the counts

	//if the counts aren't equal then return 0 (false)
	if ((target->count != source->count)){
		return 0;
	}
	//now if the counts are equal then continue
	else {
		//we have to check if the values are in the same order.
		for (int i = 0; i < target->count; ++i) {
			if (target->items[i] != source->items[i]) {
				return 0;
			}
		}
	}

	return 1;
}

// Prints the items in a list from front to rear.
void list_print(const list_dynamic_struct *source) {
    // Walk through stack from top to bottom using indexes.
    for(int i = 0; i < source->count; i++) {
        data_print(&(source->items[i]));
        printf("\n");
    }
    return;
}
