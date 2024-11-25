/**
 * -------------------------------------
 * @file  name_set_initialize.c
 * Lab 5 Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#include "name_set.h"

name_set* name_set_initialize() {
    // Allocate memory to the data structure
    name_set *set = malloc(sizeof *set);
    // Initialize the header fields.
    set->front = NULL;
    set->rear = NULL;
    return set;
}

int name_set_free(name_set **set) {
	// we have to have to check if the pointer is null and if it isn't null then we have to check if the set itself is null otherwise continue
    if (set == NULL || *set == NULL) {
        return 0;
    }

    //then we have to intialize a count so we know how many we have freed in this set
    int count = 0;
    //create a pointer to the front node with the struct name_set_node beecause that pointer has that struct type
    name_set_node *Current = (*set)->front;

    //now while that front node isn't empty then we continue
    while (Current != NULL) {
    	//get the next node in the that node struct NAME_SET_NODE *next; 	// Pointer to next node.
        name_set_node *Nextnode = Current->next;
        free(Current);  // Free the current node
        Current = Nextnode; // now we are bassically traversing down the line and deleting all the nodes by setting it to the next
        count++;
    }

    free(*set);  // Free the set itself (because we havea to free the header structure as well(
    *set = NULL; // update the pointer to nothing so it's not fasely pointing to something in memory

    return count;  // Return the number of freed nodes because that's the objective of this method
}


BOOLEAN name_set_append(name_set *set, const char *first_name, const char *last_name) {
    if (set == NULL || first_name == NULL || last_name == NULL) {
        return 0;  // Invalid input
    }

    // Allocate front node if it doesn't exist
    //basically we have to check if the front has a node for us to even append the name and if it doesn't then we make one
    if (set->front == NULL) {
    	//now we add a allocate size for the node
        set->front = (name_set_node *)malloc(sizeof(name_set_node));
        if (set->front == NULL) { // now we check if allocating sapce from above worked or not
            perror("Failed to allocate front node");
            return 0;  // Memory allocation failed
        }
        // now since it was successfully added we add a node with nothing but 0 taking up the entire size of it
        memset(set->front, 0, sizeof(name_set_node));  // Initialize the front node

        //now beacuse this is a new node there is only one node so we have to make it both point to the same node?
        set->rear = set->front;  // Rear points to the same node initially
    }

    //now if the above check said that the node existed and wasn't empty then we check for a matching name to see if it's already in the set
    // Check if the front node contains the name
    // we get a pointer with the struct "name_set_node" to access the front node
    name_set_node *FrontNode = set->front;
    //check if it's not empty and if there is already a matching name or not
    if (FrontNode->first_name[0] != '\0' && strcmp(FrontNode->first_name, first_name) == 0 && strcmp(FrontNode->last_name, last_name) == 0) {
        printf("Already have this name in the front node.\n");
        return 0;
    }

    // Check if rear node exists, if not, allocate it
    if (set->rear->next == NULL && set->rear != set->front) {
        set->rear->next = (name_set_node *)malloc(sizeof(name_set_node));
        if (set->rear->next == NULL) {
            perror("Failed to allocate rear node");
            return 0;  // Memory allocation failed
        }
        memset(set->rear->next, 0, sizeof(name_set_node));// fill in the rear node
    }

    //now we can append the name to the rear node if it's free
    if (set->rear->first_name[0] == '\0') {
        strncpy(set->rear->first_name, first_name, NAME_LEN - 1);
        set->rear->first_name[NAME_LEN - 1] = '\0';
        strncpy(set->rear->last_name, last_name, NAME_LEN - 1);
        set->rear->last_name[NAME_LEN - 1] = '\0';
        return 1;
    } else if (set->rear->next == NULL) {
        //add a new node if the rear is occupied
        set->rear->next = (name_set_node *)malloc(sizeof(name_set_node));
        if (set->rear->next == NULL) {
            perror("Failed to allocate new rear node");
            return 0;  // Memory allocation failed
        }
        memset(set->rear->next, 0, sizeof(name_set_node));  // Initialize the new rear node
        set->rear = set->rear->next;  // Move the rear pointer to the new node
        strncpy(set->rear->first_name, first_name, NAME_LEN - 1);
        set->rear->first_name[NAME_LEN - 1] = '\0';
        strncpy(set->rear->last_name, last_name, NAME_LEN - 1);
        set->rear->last_name[NAME_LEN - 1] = '\0';
        return 1;
    }

    return 0;  // if we couldnt add a name, return false
}


BOOLEAN name_set_contains(const name_set *set, const char *first_name, const char *last_name) {
    if (set == NULL || first_name == NULL || last_name == NULL) {
        return 0;
    }

    name_set_node *Current = set->front;

    while (Current != NULL){
    	if (strcmp(Current->first_name, first_name) == 0 && strcmp(Current->last_name, last_name) == 0){
    		return 1;
    	}
    	Current = Current->next;
    }
    return 0;
}

void name_set_print(const name_set *set) {
	if (set == NULL){
		return;
	}

	name_set_node *Current = set->front;
	while (Current != NULL) {
	        printf("%s, %s\n", Current->last_name, Current->first_name);
	        Current = Current->next;
	    }

}
