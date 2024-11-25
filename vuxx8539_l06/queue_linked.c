/**
 * -------------------------------------
 * @file  queue_linked.c
 * Linked Queue Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
// Includes
#include "queue_linked.h"

// Functions

queue_linked* queue_initialize() {

	queue_linked *new_queue_linked  = malloc(sizeof(queue_linked));
	new_queue_linked->count = 0;
	new_queue_linked->front = NULL;
	new_queue_linked->rear = NULL;

	return new_queue_linked;
}

void queue_free(queue_linked **source) {

    queue_node *current_node = (*source)->front;
    while (current_node != NULL){
    	queue_node *next_node = current_node->next;
    	current_node = next_node;
    	free(current_node);
    	(*source)->count--;
    }

    free(*source);
    *source = NULL;
}

BOOLEAN queue_empty(const queue_linked *source) {
	return (source->count == 0 ? 1 : 0);
}

int queue_count(const queue_linked *source){
	return source->count;
}

void queue_insert(queue_linked *source, data_ptr item) {

    queue_node *new_node = malloc(sizeof(queue_node));
    new_node->item = malloc(sizeof(int));
    *(new_node->item) = *item;

    new_node->next = NULL;

    if (source->front == NULL || *item < *(source->front->item)) {
        new_node->next = source->front;
        source->front = new_node;
        if (source->rear == NULL) {
            source->rear = new_node;
        }
    } else {
        queue_node *current_node = source->front;
        queue_node *previous_node = NULL;

        while (current_node != NULL && *item > *(current_node->item)) {
            previous_node = current_node;
            current_node = current_node->next;
        }

        new_node->next = current_node;
        previous_node->next = new_node;

        if (current_node == NULL) {
            source->rear = new_node;
        }
    }

    source->count++;
}



BOOLEAN queue_peek(const queue_linked *source, data_ptr item) {

    if (queue_empty(source)){
    	return 0;
    }

    *item = *(source->front->item);
    return 1;
}

BOOLEAN queue_remove(queue_linked *source, data_ptr *item) {
    if (queue_empty(source)) {
        return 0;
    }

    queue_node *node_to_remove = source->front;
    *item = node_to_remove->item;

    source->front = source->front->next;
    free(node_to_remove);
    source->count--;

    if (source->front == NULL) {
        source->rear = NULL;
    }

    return 1;
}

void queue_print(const queue_linked *source) {
    char string[DATA_STRING_SIZE];
    queue_node *current = source->front;

    while(current != NULL) {
        printf("%s\n", data_string(string, sizeof string, current->item));
        current = current->next;
    }
    return;
}
