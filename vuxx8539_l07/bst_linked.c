/**
 * -------------------------------------
 * @file  bst_linked.c
 * Linked BST Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "bst_linked.h"

// Macro for comparing node heights
#define MAX_HEIGHT(a,b) ((a) > (b) ? a : b)


// Local Static Helper Functions

/**
 * Initializes a new BST node with a copy of item.
 *
 * @param source - pointer to a BST source
 * @param item - pointer to the item to assign to the node
 * @return a pointer to a new BST node
 */
static bst_node* bst_node_initialize(const data_ptr item) {
    // Base case: add a new node containing a copy of item.
    bst_node *node = malloc(sizeof *node);
    node->item = malloc(sizeof *node->item);
    data_copy(node->item, item);
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * Helper function to determine the height of node - handles empty node.
 * @param node - The node to process.
 * @return The height of the current node.
 */
static int bst_node_height(const bst_node *node) {
    int height = 0;

    if(node != NULL) {
        height = node->height;
    }
    return height;
}

/**
 * Updates the height of a node. Its height is the max of the heights of its
 * child nodes, plus 1.
 * @param node The node to process.
 */
static void bst_update_height(bst_node *node) {
    int left_height = bst_node_height(node->left);
    int right_height = bst_node_height(node->right);

    node->height = MAX_HEIGHT(left_height, right_height) + 1;
    return;
}

/**
 * Inserts item into a BST. Insertion must preserve the BST definition.
 * item may appear only once in source.
 *
 * @param source - pointer to a BST
 * @param node - pointer to a node
 * @param item - the item to insert
 * @return - TRUE if item inserted, FALSE otherwise
 */
static BOOLEAN bst_insert_aux(bst_linked *source, bst_node **node, const data_ptr item) {
    BOOLEAN inserted = FALSE;

    if(*node == NULL) {
        // Base case: add a new node containing the item.
        *node = bst_node_initialize(item);
        source->count += 1;
        inserted = TRUE;
    } else {
        // Compare the node data_ptr against the new item.
        int comp = data_compare(item, (*node)->item);

        if(comp < 0) {
            // General case: check the left subsource.
            inserted = bst_insert_aux(source, &(*node)->left, item);
        } else if(comp > 0) {
            // General case: check the right subsource.
            inserted = bst_insert_aux(source, &(*node)->right, item);
        }
    }
    if(inserted) {
        // Update the node height if any of its children have been changed.
        bst_update_height(*node);
    }
    return inserted;
}

//--------------------------------------------------------------------
// Functions

// Initializes a BST.
bst_linked* bst_initialize() {
    bst_linked *source = malloc(sizeof *source);
    source->root = NULL;
    source->count = 0;
    return source;
}



//BST AUX
void bst_free_aux(bst_linked *source, bst_node **node){
	if((*node) == NULL){
		return;
	}

	bst_free_aux(source, &(*node)->left);
	bst_free_aux(source, &(*node)->right);
	data_free(&(*node)->item);
	(*node)->item = NULL;
	free(*node);
	(*node) = NULL;

}

// frees a BST.
void bst_free(bst_linked **source) {

	bst_free_aux((*source), &(*source)->root);

    free(*source);
    (*source) = NULL;
    return;
}

// Determines if a BST is empty.
BOOLEAN bst_empty(const bst_linked *source) {
    return (source->count == 0);
}

// Determines if a BST is full.
BOOLEAN bst_full(const bst_linked *source) {
    return FALSE;
}

// Returns number of items in a BST.
int bst_count(const bst_linked *source) {
    return (source->count);
}

void bst_inorder_aux(bst_node *node, data_ptr *Array, int *index){
	if(node == NULL){
		return;
	}

	//building up the stack to keep going left until we can't
	bst_inorder_aux(node->left, Array, index);

	//once we can't go left anymore add it into the array
	Array[*index] = node->item;
	//we index to move onto the next slot
	(*index)++;

	//go to the right and then keep going l	eft until we can't.... rinse and repeats
	bst_inorder_aux(node->right, Array, index);
}

// Copies the contents of a BST to an array in inorder.
void bst_inorder(const bst_linked *source, data_ptr *items) {
	//items is an array that is being passed
	//pass the address so we can refer to the same arraay each time
	int index = 0; // we pass an index to know where we are at in the array
	bst_inorder_aux(source->root, items, &index);
    return;
}

void bst_preorder_aux(bst_node *node, data_ptr *Array, int *index){
	if(node == NULL){
		return;
	}

	Array[*index] = node->item;
	(*index)++;

	bst_preorder_aux(node->left, Array, index);

	bst_preorder_aux(node->right, Array, index);

}

// Copies the contents of a BST to an array in preorder.
void bst_preorder(const bst_linked *source, data_ptr *items) {
	int index = 0;
	bst_preorder_aux(source->root, items, &index);
    return;
}

// Copies the contents of a BST to an array in postorder.
void bst_postorder(const bst_linked *source, data_ptr *items) {

    // your code here
    return;
}

// Inserts a copy of an item into a BST.
BOOLEAN bst_insert(bst_linked *source, const data_ptr item) {
    return bst_insert_aux(source, &(source->root), item);
}



// Retrieves a copy of a value matching key in a BST.
BOOLEAN bst_retrieve(bst_linked *source, const data_ptr key, data_ptr item) {

	bst_node *RootNode = source->root;

	while(RootNode != NULL){
		if(data_compare(key, RootNode->item) == 0){
			*item = *(RootNode->item);
			return TRUE;
		}else if(data_compare(key, RootNode->item) < 0){
			//go left
			RootNode = RootNode->left;
		}else{
			//go right
			RootNode = RootNode->right;
		}
	}

    return FALSE;
}

// Removes a value matching key in a BST.
BOOLEAN bst_remove(bst_linked *source, const data_ptr key, data_ptr item) {

    // your code here

    return FALSE;
}

// Copies source to target.
void bst_copy(bst_linked **target, const bst_linked *source) {

    // your code here

}

// Finds the maximum item in a BST.
BOOLEAN bst_max(const bst_linked *source, data_ptr item) {

    // your code here

    return FALSE;
}


int bst_min_aux(bst_linked *source, bst_node **node, int min){
	if((*node) == NULL){
		return 0;
	}

	//bst_min_aux
}


// Finds the minimum item in a BST.
BOOLEAN bst_min(const bst_linked *source, data_ptr item) {

    return TRUE;
}


void bst_leaf_count_aux(bst_node *node, int *leafcount) {
    if (node == NULL) {
        return;
    }

    if(node->left == NULL && node->right == NULL){
    	//referencing to the original tracker we had from the caller
    	(*leafcount)++;
    }

   //go next
   bst_leaf_count_aux(node->left, leafcount);
   bst_leaf_count_aux(node->right, leafcount);

}


// Finds the number of leaf nodes in a tree.
int bst_leaf_count(const bst_linked *source) {
	int LeafCount = 0;
    bst_leaf_count_aux(source->root, &LeafCount);
    return LeafCount;
}

// Finds the number of nodes with one child in a tree.
int bst_one_child_count(const bst_linked *source) {

    // your code here

    return 0;
}

// Finds the number of nodes with two children in a tree.
int bst_two_child_count(const bst_linked *source) {

    // your code here

    return 0;
}

// Determines the number of nodes with zero, one, and two children.
// (May not call bst_leaf_count, bst_one_child_count, or bst_two_child_count.)
void bst_node_counts(const bst_linked *source, int *zero, int *one, int *two) {

    // your code here

    return;
}


BOOLEAN bst_balanced_aux(bst_node *node, int *height) {
    if (node == NULL) {
        *height = 0;
        return TRUE;
    }

    int LeftHeight = 0, RightHeight = 0;


    BOOLEAN left_balance = bst_balanced_aux(node->left, &LeftHeight);

    BOOLEAN right_balance = bst_balanced_aux(node->right, &RightHeight);


    *height = (LeftHeight > RightHeight ? LeftHeight : RightHeight) + 1;
    BOOLEAN nodeBalance = abs(LeftHeight - RightHeight) <= 1;

    return left_balance && right_balance && nodeBalance;
}

// Main function to check if the entire BST is balanced
BOOLEAN bst_balanced(const bst_linked *source) {
    int height = 0;
    return bst_balanced_aux(source->root, &height);
}


// Determines whether or not a tree is a valid BST.
BOOLEAN bst_valid(const bst_linked *source) {

    // your code here

    return FALSE;
}

// Determines if two trees contain same data in same configuration.
BOOLEAN bst_equals(const bst_linked *target, const bst_linked *source) {

	//do a count check first

    return FALSE;
}

/**
 * Private helper function to print contents of BS in preorder.
 *
 * @param to_string - function to print data_ptr
 * @param node - pointer to bst_node
 */
static void bst_print_aux(bst_node *node) {
    char string[DATA_STRING_SIZE];

    if(node != NULL) {
        printf("%s\n", data_string(string, DATA_STRING_SIZE, node->item));
        bst_print_aux(node->left);
        bst_print_aux(node->right);
    }
    return;
}

// Prints the items in a BST in preorder.
void bst_print(const bst_linked *source) {
    printf("  count: %d, height: %d, items:\n", source->count, source->root->height);
    bst_print_aux(source->root);
    printf("\n");
    return;
}
