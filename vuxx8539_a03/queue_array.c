/**
 * -------------------------------------
 * @file  queue_array.c
 * queue_array Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#include "queue_array.h"

// Functions

/**
 * Initializes a queue.
 *
 * @param queue - the queue to initialize.
 */
void queue_initialize(queue_struct *source) {

	source->capacity = QUEUE_INIT;
	source->count = 0;
	source->front = 0;
	source->rear = 0;
    return;
}

/**
 * Determines if a queue is empty.
 *
 * @param source - pointer to a queue.
 * @return - true if source is empty, false otherwise.
 */
bool queue_empty(const queue_struct *source) {
    return source->count == 0;
}

/**
 * Determines if a queue is full.
 *
 * @param source - pointer to a queue.
 * @return - true if source is full, false otherwise.
 */
bool queue_full(const queue_struct *source) {
	return source->count == source->capacity;
}

/**
 * Returns the number of items in a queue.
 *
 * @param source - pointer to a queue.
 * @return - the number of items in source.
 */
int queue_count(const queue_struct *source) {
	return source->count;
}

/**
 * Inserts an item into a queue.
 *
 * @param source - pointer to a queue.
 * @param item - the item to insert.
 * @return - true if item inserted, false otherwise (queue is full)
 */
bool queue_insert(queue_struct *source, data_type *item) {
	// if the queue is full we don't want to add anything
	if (queue_full(source)){
		return 0;
	}

	//otherwise if the queue has space we can add.. also
	//check for single item
	if(queue_empty(source)){ // this checks for a single item
		source->items[source->front] = *item;
		source->count++;
		//since it's single item then the rear has to match the fronts
		source->rear = source->front;
		return 1;
	}else{
		//this is for if there is already a node
		source->rear = source->rear + 1; // increase the index first
		source->items[source->rear] = *item;
		//dont change the front and rear is already updated
		//now increase the count
		source->count++;
		return 1;
	}
}

/**
 * Returns a copy of the item on the front of a queue. queue is unchanged.
 *
 * @param source - pointer to a queue.
 * @param item - the item to peek.
 * @return - true if item peeked, false otherwise (queue is empty)
 */
bool queue_peek(const queue_struct *source, data_type *item) {
	if (queue_empty(source)){
			return 0;
		}else{
			*item = source->items[source->front];
			return 1;
		}
}

/**
 * Returns and removes the item on the front of a queue.
 *
 * @param source - pointer to a queue.
 * @param item - the item to peek.
 * @return - true if item removed, false otherwise (queue is empty)
 */
bool queue_remove(queue_struct *source, data_type *item) {
	if (queue_empty(source)){
		return 0;
	}

	if (source->count == 1){
			*item = source->items[source->front];
			source->count = 0;
			source->front = 0;
			source->rear = 0;
			return 1;
		}

	if(source->count > 1){ // then there are two items
		*item = source->items[source->front];
		//now we update the front to index to the next item?
		source->front = source->front + 1;
		//then minus the count by 1s
		source->count--;
		// we need to check if it's only 1
		if (source->count == 1){
			source->rear = source->front;
			return 1;
		}
	}

	return 1;
}

/**
 * Prints the items in a queue from front to rear.
 * (For testing only).
 *
 * @param source - pointer to a queue
 */
void queue_print(const queue_struct *sourcee) {
	if (queue_empty(sourcee)){
		printf("Empty");
	}else{
		printf("Items in queue: \n");
		for (int i = 0; i < sourcee->count; ++i){
			printf("%d\n", sourcee->items[i]);
		}
	}
    return;
}
