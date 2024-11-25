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
#include "stack_dynamic.h"
#include "queue_dynamic.h"
#include "pq_dynamic.h"
#include "list_dynamic.h"

#define SEP "-------------------------------------\n"

void test_stack_generic(data_type values[], int count) {
    data_type item;

    stack_dynamic_struct *source = NULL;
    stack_initialize(&source, STACK_INIT);

    printf("Testing stack_dynamic\n");
    printf(SEP);
    printf("stack_empty: %s\n", BOOL_TO_STR(stack_empty(source)));
    printf(SEP);
    printf("stack_push\n");

    for(int i = 0; i < count; i++) {
        printf("push: ");
        data_print(&values[i]);
        printf("\n");
        stack_push(source, &values[i]);
    }
    for(int i = 0; i < count; i++) {
        printf("push: ");
        data_print(&values[i]);
        printf("\n");
        stack_push(source, &values[i]);
    }
    printf(SEP);
    printf("stack_empty: %s\n", BOOL_TO_STR(stack_empty(source)));
    printf(SEP);
    printf("stack_peek\n");
    stack_peek(source, &item);
    printf("item: ");
    data_print(&item);
    printf("\n");
    printf(SEP);
    printf("stack_print\n");
    stack_print(source);
    printf(SEP);
    printf("stack_pop\n");

    while(!stack_empty(source)) {
        stack_pop(source, &item);
        printf("popped: ");
        data_print(&item);
        printf("\n");
    }
}

void test_queue_generic(data_type values[], int count) {

    queue_dynamic_struct* mylist = NULL;
    queue_initialize(&mylist, 7);

    for (int i = 0; i < count; i++) {
        queue_insert(mylist, &values[i]);
    }

    queue_print(mylist);

    printf("mylist capacity is now: %d\n\n", mylist->capacity);

    data_type TopValueRemovedIs;
    queue_remove(mylist, &TopValueRemovedIs);
    printf("The Top value removed was: %d\n", TopValueRemovedIs);


    queue_print(mylist);


    queue_destroy(&mylist);
}

void test_pq_generic(data_type values[], int count) {
    pq_dynamic_struct *mylist = NULL;
    pq_initialize(&mylist, 7);

    printf("EmptyCheck:%s ", pq_empty(mylist) ? "True\n\n" : "False\n\n");

    printf("\n\n-----------------------------------------\n");

    for (int i = 0; i < count; i++) {
        pq_insert(mylist, &values[i]);
    }

    //printing out the list to check 
    printf("AfterInsertion:\n");
    pq_print(mylist);


    printf("\n\n-----------------------------------------");

    data_type PqRemovedValue;
    pq_remove(mylist, &PqRemovedValue);

    printf("\nAfterRemoval\n");
    pq_print(mylist);

    printf("\n\n-----------------------------------------\n");

    printf("Checking if queue is empty: %s", pq_empty(mylist) ? "True\n" : "False\n");

    printf("\n\n-----------------------------------------\n");

    printf("Checking if queue is full: %s", pq_full(mylist) ? "True\n" : "False\n");

    printf("\n\n-----------------------------------------\n");

    printf("The count of the queue is: %d", pq_count(mylist));

    printf("\n\n-----------------------------------------\n");

    data_type PeekedValue;
    pq_peek(mylist, &PeekedValue);
    printf("The Peek Value is: %d", PeekedValue);

    printf("\n\n-----------------------------------------\n");
    printf("Destroying PQ");
    pq_destroy(&mylist);
}

void print_list_generic(list_dynamic_struct* FirstList, list_dynamic_struct* SecondList) {
    printf("Values in FirstList\n");
    list_print(FirstList);
    printf("Values in SecondList\n");
    list_print(SecondList);
    printf("\n\n");
}

void test_list_generic(data_type values[], int count) {
        list_dynamic_struct* FirstList = NULL;
        list_dynamic_struct* SecondList = NULL;
        list_initialize(&FirstList, 5);
        list_initialize(&SecondList, 5);

        for (int i = 0; i < count; i++) {
            list_append(FirstList, &values[i]);
            list_append(SecondList, &values[i]);
        }

        // Printing list
        print_list_generic(FirstList, SecondList);

        // Testing list_empty method
        printf("FirstList Empty Check: %d\n", list_empty(FirstList));
        printf("SecondList Empty Check: %d\n\n", list_empty(SecondList));

        // Testing list_full method
        printf("FirstList Full Check: %d\n", list_full(FirstList));
        printf("SecondList Full Check: %d\n\n", list_full(SecondList));

        // Testing list_append method
        int AppendMethodValue = 6969;
        printf("FirstList Append Check: %d\n", list_append(FirstList, &AppendMethodValue));
        printf("SecondList Append Check: %d\n\n", list_append(SecondList, &AppendMethodValue));

        // Printing list
        print_list_generic(FirstList, SecondList);

        // Testing list_count method
        printf("FirstList Count Check: %d\n", list_count(FirstList));
        printf("SecondList Count Check: %d\n\n", list_count(SecondList));

        // Testing list_insert method
        int InsertMethodValue = 9999;
        int IndexInsertLocation = 0;
        printf("FirstList Insert Check: %d\n", list_insert(FirstList, &InsertMethodValue, IndexInsertLocation));
        printf("SecondList Insert Check: %d\n\n", list_insert(SecondList, &InsertMethodValue, IndexInsertLocation));

        // Printing list
        print_list_generic(FirstList, SecondList);

        // Testing list_peek method
        data_type peekValue = 0;
        printf("FirstList Peek Check: %d, Value: %d\n", list_peek(FirstList, &peekValue), peekValue);
        printf("SecondList Peek Check: %d, Value: %d\n\n", list_peek(SecondList, &peekValue), peekValue);


        // Testing list_index_remove method
        int IndexRemoveLocation = 0;
        data_type removedValue;
        printf("FirstList Index Remove Check: %d\n", list_index_remove(FirstList, &removedValue, IndexRemoveLocation));
        printf("SecondList Index Remove Check: %d\n\n", list_index_remove(SecondList, &removedValue, IndexRemoveLocation));

        // Printing list
        print_list_generic(FirstList, SecondList);
        

        // Testing list_key_find method
        data_type keyToFind = 6969;
        printf("FirstList Key Find Check: %d\n", list_key_find(FirstList, &keyToFind, &peekValue));
        printf("SecondList Key Find Check: %d\n", list_key_find(SecondList, &keyToFind, &peekValue));
        printf("%d\n\n", peekValue);

        // Testing list_key_remove method
        data_type keyToRemove = 7;
        printf("FirstList Key Remove Check: %d\n", list_key_remove(FirstList, &keyToRemove, &removedValue));
        printf("SecondList Key Remove Check: %d\n\n", list_key_remove(SecondList, &keyToRemove, &removedValue));

        // Printing list
        print_list_generic(FirstList, SecondList);

        // Testing list_key_index method
        data_type KeyIndexValue = 6969;
        printf("FirstList Key Index Check -> The value is at index: %d\n", list_key_index(FirstList, &KeyIndexValue));
        printf("SecondList Key Index Check -> The value is at index: %d\n\n", list_key_index(SecondList, &KeyIndexValue));

        // Testing list_key_contains method
        data_type KeyContainsValue = 7;
        printf("FirstList Key Contains Check: %d\n", list_key_contains(FirstList, &KeyContainsValue));
        printf("SecondList Key Contains Check: %d\n\n", list_key_contains(SecondList, &KeyContainsValue));

        // Testing list_key_count method
        data_type KeyCountValue = 3; 
        printf("FirstList Key Count Check -> The amount of times this key appears is: %d\n", list_key_count(FirstList, &KeyCountValue));
        printf("SecondList Key Count Check -> The amount of times this key appears is: %d\n\n", list_key_count(SecondList, &KeyCountValue));


        // Testing list_max method
        data_type maxValue = 0;
        printf("FirstList Max Check: %d, Value: %d\n", list_max(FirstList, &maxValue), maxValue);
        printf("SecondList Max Check: %d, Value: %d\n\n", list_max(SecondList, &maxValue), maxValue);

        // Testing list_min method
        data_type minValue = 0;
        printf("FirstList Min Check: %d, Value: %d\n", list_min(FirstList, &minValue), minValue);
        printf("SecondList Min Check: %d, Value: %d\n\n", list_min(SecondList, &minValue), minValue);

        // Testing list_clean method
        list_clean(FirstList);
        list_clean(SecondList);

        // Printing list
        print_list_generic(FirstList, SecondList);

        printf("FirstList After Clean Count: %d\n", list_count(FirstList));
        printf("SecondList After Clean Count: %d\n\n", list_count(SecondList));

        data_type RemoveItemEqualTest;
        printf("%d\n", list_index_remove(FirstList, &RemoveItemEqualTest, 0));

        data_type RemoveItemEqualTestTwo;
        printf("%d\n", list_index_remove(SecondList, &RemoveItemEqualTestTwo, 3));

        // Printing list
        print_list_generic(FirstList, SecondList);

        // Testing list_equal method
        printf("List Equal Check: %d\n\n", list_equal(FirstList, SecondList));


        list_destroy(&FirstList);
        list_destroy(&SecondList);
}

void test_stack_int() {
    // Test the stack with integer data.
    data_type values[] = {2, 4, 1, 7, 4, 2, 9};
    const int COUNT = sizeof values / sizeof *values;
    test_stack_generic(values, COUNT);
}

void test_queue_int() {
    // Test the queue with integer data.
    data_type values[] = {2, 4, 1, 7, 4, 2, 9};
    const int COUNT = sizeof values / sizeof *values;
    test_queue_generic(values, COUNT);
}

void test_pq_int() {
    // Test the priority queue with integer data.
    data_type values[] = {2, 4, 1, 7, 4, 2, 9};
    const int COUNT = sizeof values / sizeof *values;
    test_pq_generic(values, COUNT);
}

void test_list_int() {
    // Test the list with integer data.
    data_type values[] = {1,3,3,7};
    const int COUNT = sizeof values / sizeof *values;
    test_list_generic(values, COUNT);
}

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);

    printf(SEP);
    test_stack_int();
    printf(SEP);
    test_queue_int();
    printf(SEP);
    test_pq_int();
    printf(SEP);
    test_list_int();

    return (0);
}
