/**
 * -------------------------------------
 * @file  main.c
 * file description
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

#include "data.h"
#include "movie_utilities.h"
#include "stack_array.h"
#include "queue_array.h"
#include "pq_array.h"

#define SEP "-------------------------------------\n"

void test_stack_generic(data_type values[], int count) {
    data_type item;

    stack_struct source;
    stack_initialize(&source);

    printf("Testing stack_array\n");
    printf(SEP);
    printf("stack_empty: %s\n", BOOL_TO_STR(stack_empty(&source)));
    printf(SEP);
    printf("stack_push\n");

    for(int i = 0; i < count; i++) {
        printf("push: ");
        data_print(&values[i]);
        printf("\n");
        stack_push(&source, &values[i]);
    }
    printf(SEP);
    printf("stack_empty: %s\n", BOOL_TO_STR(stack_empty(&source)));
    printf(SEP);
    printf("stack_peek\n");
    stack_peek(&source, &item);
    printf("item: ");
    data_print(&item);
    printf("\n");
    printf(SEP);
    printf("stack_print\n");
    stack_print(&source);
    printf(SEP);
    printf("stack_pop\n");

    while(!stack_empty(&source)) {
        stack_pop(&source, &item);
        printf("popped: ");
        data_print(&item);
        printf("\n");
    }
}

void test_stack_int() {
    // Test the stack with integer data.
    data_type values[] = {2, 4, 1, 7, 4, 2, 9};
    const int COUNT = sizeof values / sizeof *values;
    test_stack_generic(values, COUNT);
}


void test_stack_movie() {
// Test the stack with movie data
movie_array_struct movies;
FILE *fp = fopen("movies.txt", "r");
read_movies(&movies, fp);
fclose(fp);
test_stack_generic(movies.items, movies.count);
}


void test_queue_int() {
    queue_struct myQueue;
    data_type item;

    queue_initialize(&myQueue);
    printf("Testing queue initialization...\n");
    if (queue_empty(&myQueue) && myQueue.count == 0) {
        printf("Queue initialized successfully.\n");
    } else {
        printf("Queue initialization failed.\n");
    }

    for (int i = 0; i < 3; i++) {
        item = i + 1;
        if (queue_insert(&myQueue, &item)) {
            printf("Inserted %d into the queue.\n", item);
        } else {
            printf("Failed to insert %d into the queue.\n", item);
        }
    }

    queue_print(&myQueue);

    if (queue_peek(&myQueue, &item)) {
        printf("Peeked item: %d\n", item);
    } else {
        printf("Failed to peek, queue is empty.\n");
    }


    while (!queue_empty(&myQueue)) {
        if (queue_remove(&myQueue, &item)) {
            printf("Removed item: %d\n", item);
        } else {
            printf("Failed to remove item, queue is empty.\n");
        }
    }


    if (queue_empty(&myQueue)) {
        printf("Queue is empty after removals.\n");
    } else {
        printf("Queue is not empty after removals.\n");
    }


    for (int i = 0; i < QUEUE_INIT; i++) {
        item = i + 10;
        if (!queue_insert(&myQueue, &item)) {
            printf("Queue is full, failed to insert %d.\n", item);
        }
    }

    queue_print(&myQueue);
}

void test_pq_int() {
    pq_struct pq;
    pq_initialize(&pq);

    printf("Inserting items into the priority queue:\n");
    for (int i = 0; i < 5; i++) {
        data_type item = (5 - i) * 10;
        if (pq_insert(&pq, &item)) {
            printf("Inserted: %d\n", item);
        } else {
            printf("Failed to insert: %d\n", item);
        }
    }

    printf("Priority Queue after insertions:\n");
    pq_print(&pq);

    data_type peeked_item;
    if (pq_peek(&pq, &peeked_item)) {
        printf("Peeked item: %d\n", peeked_item);
    } else {
        printf("Failed to peek, queue is empty.\n");
    }

    data_type removed_item;
    if (pq_remove(&pq, &removed_item)) {
        printf("Removed item: %d\n", removed_item);
    } else {
        printf("Failed to remove, queue is empty.\n");
    }

    printf("Priority Queue after removal:\n");
    pq_print(&pq);
}


int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);

    test_stack_int();
    test_stack_movie();
    test_queue_int();
    test_pq_int();
    printf(SEP);
    return (0);
}
