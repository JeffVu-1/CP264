/**
 * -------------------------------------
 * @file  main.c
 * Lab 7 Main Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxxx8539@mylaurier.ca
 *
 * @version 2024-03-01
 *
 * -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "bst_linked.h"

/**
 * Simple BST testing.
 */
void test_bst(void) {
    // Define some arbitrary test data
    int numbers[] = {11, 7, 6, 9, 8, 15, 12, 18};
    int count = sizeof numbers / sizeof *numbers;
    data_ptr items[count];

    for(int i = 0; i < count; i++) {
        items[i] = malloc(sizeof items);
        items[i] = &numbers[i];
    }

    // Define a Two BSTs
    bst_linked *source = bst_initialize();
    bst_linked *target = bst_initialize();

    //insert the values into source
    for(int i = 0; i < count; i++) {
        bst_insert(source, items[i]);
    }

    //testing valid bst
    printf("Valid Test: %s\n", BOOL_TO_STR(bst_valid(source)));

    //Equal test should be false
    printf("Equal Test: %s\n", BOOL_TO_STR(bst_equals(source, target)));

    //Testing bst_copy
    printf("Testing bst_copy\n");
    bst_copy(&target, source);
    printf("source: \n");
    bst_print(source);
    printf("target: \n");
    bst_print(target);

    //Equal test should be true
    printf("Equal Test: %s\n", BOOL_TO_STR(bst_equals(source, target)));

    //Testing bst_max and bst_min
    data_ptr MaxItemData = malloc(sizeof *MaxItemData);
    bst_max(source, MaxItemData);
    printf("Max Item: %d\n", *MaxItemData);

    data_ptr MinItemData = malloc(sizeof *MinItemData);
    bst_min(source, MinItemData);
    printf("Min Item: %d\n", *MinItemData);
    
    //testing bst_leaf_count
    printf("Leaf Count: %d\n", bst_leaf_count(source));

    //testing bst_one_child_count
    printf("One Child Count: %d\n", bst_one_child_count(source));

    //testing bst_two_child_count
    printf("Two Child Count: %d\n", bst_two_child_count(source));

    //printing bst_node_counts
    printf("Node Counts: \n");
    data_ptr Zero = malloc(sizeof *Zero);
    data_ptr One = malloc(sizeof *One);
    data_ptr Two = malloc(sizeof *Two);
    bst_node_counts(source, Zero, One, Two);
    printf("Zero Child Count: %d\n", *Zero);
    printf("One Child Count: %d\n", *One);
    printf("Two Child Count: %d\n", *Two);


    printf("empty: %s\n", BOOL_TO_STR(bst_empty(source)));
    printf("full:  %s\n", BOOL_TO_STR(bst_full(source)));
    printf("count: %d\n", bst_count(source));
    printf("Insert test values:\n");

    for(int i = 0; i < count; i++) {
        bst_insert(source, items[i]);
    }

    bst_print(source);
    printf("empty: %s\n", BOOL_TO_STR(bst_empty(source)));
    printf("full:  %s\n", BOOL_TO_STR(bst_full(source)));
    printf("count: %d\n", bst_count(source));
    printf("leaf_count: %d\n", bst_leaf_count(source));
    printf("balanced: %s\n", BOOL_TO_STR(bst_balanced(source)));
    data_ptr values[count];
    printf("inorder:   {");
    bst_inorder(source, values);

    for(int i = 0; i < bst_count(source); i++) {
        printf("%d, ", *values[i]);
    }
    printf("}\n");
    printf("Remove %d:\n", *items[0]);
    data_ptr item = items[0];
    bst_remove(source, item, item);
    printf("  removed: %d\n", *item);
    printf("inorder:  {");
    bst_inorder(source, values);

    for(int i = 0; i < bst_count(source); i++) {
        printf("%d, ", *values[i]);
    }
    printf("}\n");

    printf("Destroy the BST\n");
    bst_free(&source);
}

/**
 * Test the file and string functions.
 *
 * @param argc - unused
 * @param argv - unused
 * @return EXIT_SUCCESS
 */
int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);

    test_bst();

    getchar();
    return (EXIT_SUCCESS);
}
