/**
 * -------------------------------------
 * @file  list_linked.c
 * Linked List Source Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 0000-00-00
 *
 * -------------------------------------
 */
#include "list_linked.h"

//==================================================================================
// Private helper functions - use in public functions

/**
 * Determines if an index in source is valid.
 *
 * @param source - pointer to source
 * @param i - index to check
 * @return - TRUE if i is a valid index, FALSE otherwise
 */
static BOOLEAN valid_index(const list_linked *source, int i) {
    return ((i >= 0) && (i <= source->count));
}

/**
 * Performs a linear search on source for key.
 * Updates prev and curr pointers.
 *
 * @param source - pointer to source
 * @param key - key to search for
 * @param prev - pointer to node previous to node containing key
 * @param curr - pointer to node containing key
 * @return - -1 if key is not found, index of node if found
 */
static int linear_search(const list_linked *source, const data_ptr key, list_node **prev, list_node **curr) {
    if(source == NULL || source->front == NULL){
        return -1;
    }

    list_node *CurrentNode = source->front;
    list_node *previous = NULL;
    int index = 0;
    while(CurrentNode != NULL){
        if(*CurrentNode->item == *key){
            *prev = previous;
            *curr = CurrentNode;
            return index;
        }
        previous = CurrentNode;
        CurrentNode = CurrentNode->next;
        index++;
    }

    return -1;
}

/**
 * Frees list_node memory.
 *
 * @param node - node to free
 */
static void free_node(list_node **node) {
    // Free the removed node.
    data_free(&(*node)->item);
    free(*node);
    *node = NULL;
    return;
}

/**
 * Moves front node of source to target. Does nothing if source is empty.
 *
 * @param target - pointer to target
 * @param source - pointer to source
 */
static void move_front_to_rear(list_linked *target, list_linked *source) {
    if (list_empty(source)) {
        return;
    }

    list_node *MoveNode = source->front;

    source->front = MoveNode->next;
    source->count--;

    if (source->front == NULL) {
        source->rear = NULL;
    }

    MoveNode->next = NULL;
    if (target->rear == NULL) {
        target->front = MoveNode;
        target->rear = MoveNode;
    } else {
        target->rear->next = MoveNode;
        target->rear = MoveNode;
    }
    target->count++;
    return;
}

/**
 * Appends all nodes of source to rear of target. source is empty when finished.
 * MUST NOT USE LOOP!
 *
 * @param target - pointer to target
 * @param source - pointer to source
 */
static void append_nodes(list_linked *target, list_linked *source) {
    if (source == NULL || source->front == NULL) {
        return;
    }

    if (target == NULL || target->front == NULL) {
        target->front = source->front;
        target->rear = source->rear;
        target->count = source->count;
    } else {
        target->rear->next = source->front;
        target->rear = source->rear;
        target->count += source->count;
    }

    source->front = NULL;
    source->rear = NULL;
    source->count = 0;
}

//==================================================================================
// Functions

// Initializes a list.
list_linked* list_initialize() {
    list_linked *source = malloc(sizeof *source);
    source->front = NULL;
    source->rear = NULL;
    source->count = 0;
    return source;
}

// Destroys a list.
void list_free(list_linked **source) {
    if(source == NULL || *source == NULL){
        return;
    }

    list_node *CurrentNode = (*source)->front;\
    while(CurrentNode != NULL){
        list_node *NextNode = CurrentNode->next;
        free(CurrentNode);
        CurrentNode = NextNode;
    }

    free(*source);
    (*source) = NULL;

    return;
}

// Determines if a list is empty.
BOOLEAN list_empty(const list_linked *source) {
    return source->count == 0;
}

// Determines if the list is full.
BOOLEAN list_full(const list_linked *source) {
    return FALSE;
}

// Appends a item to the end of a list.
BOOLEAN list_append(list_linked *source, data_ptr item) {
    if(source == NULL){
        return FALSE;
    }

    list_node *NewNode = malloc(sizeof(list_node));
    if(NewNode == NULL){
        return FALSE;
    }

    NewNode->item = malloc(sizeof(int));
      if (NewNode->item == NULL) {
        free(NewNode);
        return FALSE;
    }

    *NewNode->item = *item;
    NewNode->next = NULL;

    if (source->count == 0){
        source->front = NewNode;
        source->rear = NewNode;
    }else{
        source->rear->next = NewNode;
        source->rear = NewNode;
    }

    source->count++;
    return TRUE;
}

// Prepends a item to the front of a list.
BOOLEAN list_prepend(list_linked *source, data_ptr item) {
    if(source == NULL){
        return FALSE;
    }

    list_node *NewNode = malloc(sizeof(list_node));
    if(NewNode == NULL){
        return FALSE;
    }
    NewNode->item = malloc(sizeof(int));
    if(NewNode->item == NULL){
        free(NewNode);
        return FALSE;
    }

    *NewNode->item = *item;

    NewNode->next = source->front;
    source->front = NewNode;
    source->count++;

    return TRUE;
}

// Returns the number of items in the list.
int list_count(const list_linked *source) {
    return source->count;
}

// Inserts a item to a list at location i.
BOOLEAN list_insert(list_linked *source, data_ptr item, int i) {

    list_node *NewNode = malloc(sizeof(list_node));
    if(NewNode == NULL){
        return FALSE;
    }
    NewNode->item = malloc(sizeof(int));
    if(NewNode->item == NULL){
        free(NewNode);
        return FALSE;
    }
    *NewNode->item = *item;
    NewNode->next = NULL;


    if(i < 0){
        NewNode->next = source->front;
        source->front = NewNode;
        if (source->count == 0) {
            source->rear = NewNode;
        }
    }else if(i > source->count){
        if (source->count == 0) {
            source->front = NewNode;
        } else {
            source->rear->next = NewNode;
        }
        source->rear = NewNode;
    }else{
        list_node *current = source->front;
        list_node *previous = NULL;

        for(int j = 0; j < i; ++j){
            previous = current;
            current = current->next;
        }

        previous->next = NewNode;
        NewNode->next = current;
    }

    source->count++;
    return TRUE;
}

// Returns a copy of the front of a list.
BOOLEAN list_peek(const list_linked *source, data_ptr item) {
    if(source == NULL){
        return FALSE;
    }

    *item = *source->front->item;
    return TRUE;
}

// Returns a copy of the item matching key in a list.
BOOLEAN list_key_find(const list_linked *source, const data_ptr key, data_ptr item) {
    if(source == NULL || source->front == NULL){
        return FALSE;
    }

    list_node *CurrentNode = source->front;
    while(CurrentNode != NULL){
        if(*CurrentNode->item == *key){
            *item = *CurrentNode->item;
            return TRUE;
        }

        CurrentNode = CurrentNode->next;
    }

    return FALSE;
}

// Removes and returns the item matching key from the list.
BOOLEAN list_key_remove(list_linked *source, const data_ptr key, data_ptr item) {
    if (source == NULL || source->front == NULL){
        return FALSE;
    }

    list_node *current = source->front;
    list_node *previous = NULL;

    while(current != NULL && *current->item != *key){
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        return FALSE;
    }

    *item = *current->item;

    if (previous == NULL) {
        source->front = current->next;
    } else {
        previous->next = current->next;
    }

    if (current == source->rear) {
        source->rear = previous;
    }

    free(current->item);
    free(current);
    source->count--;
    return TRUE;
}

BOOLEAN list_remove_front(list_linked *source, data_ptr item) {
    if(source == NULL || source->front == NULL){
        return FALSE;
    }

    list_node *node_to_remove = source->front;

    *item = *node_to_remove->item;

    source->front = node_to_remove->next;

    if (source->front == NULL) {
        source->rear = NULL;
    }

    free(node_to_remove->item);
    free(node_to_remove);

    source->count--;
    return TRUE;
}

// Returns the index of key in list. -1 if key not in list.
int list_key_index(const list_linked *source, const data_ptr key) {
    if(source == NULL || source->front == NULL){
        return -1;
    }

    int index = 0;
    list_node *CurrentNode = source->front;

    while(CurrentNode != NULL){
        if(*CurrentNode->item == *key){
            return index;
        }
        index++;
        CurrentNode = CurrentNode->next;
    }

    return -1;
}

// Determines if key is in a list.
BOOLEAN list_key_contains(const list_linked *source, const data_ptr key) {
    if(source == NULL || source->front == NULL){
        return FALSE;
    }

    list_node *CurrentNode = source->front;

    while(CurrentNode != NULL){
        if(*CurrentNode->item == *key){
            return TRUE;
        }
        CurrentNode = CurrentNode->next;
    }

    return FALSE;
}

// Determines number of times key appears in list.
int list_key_count(const list_linked *source, const data_ptr key) {
    if (source == NULL || source->front == NULL){
        return 0;
    }

    int count = 0;
    list_node *CurrentNode = source->front;

    while(CurrentNode != NULL){
        if(*CurrentNode->item == *key){
            count++;
        }
        CurrentNode = CurrentNode->next;
    }

    return count;
}

// Removes and returns the item at index i from a list.
BOOLEAN list_index_remove(list_linked *source, data_ptr item, int i) {
    if(source == NULL || source->front == NULL){
        return FALSE;
    }

    list_node *current = source->front;
    list_node *previous = NULL;

    for(int j = 0; j < i; ++j){
        previous = current;
        current = current->next;
    }

    if(current == NULL){
        return FALSE;
    }

    *item = *current->item;

    if (previous == NULL) {
        source->front = current->next;
    } else {
        previous->next = current->next;
    }

    if (current == source->rear) {
        source->rear = previous;
    }

    free(current->item);
    free(current);
    source->count--;
    return TRUE;
}

// Finds the maximum item in a list.
BOOLEAN list_max(const list_linked *source, data_ptr item) {
    if(source == NULL || source->front == NULL){
        return FALSE;
    }

    int MaxItem = *source->front->item;
    list_node *currentnode = source->front;

    while(currentnode != NULL){
        if(*currentnode->item > MaxItem){
            MaxItem = *currentnode->item;
        }
        currentnode = currentnode->next;
    }

    *item = MaxItem;

    return TRUE;
}

// Finds the minimum item in a list.
BOOLEAN list_min(const list_linked *source, data_ptr item) {
    if(source == NULL || source->front == NULL){
        return FALSE;
    }

    int MinItem = *source->front->item;
    list_node *currentnode = source->front;

    while(currentnode != NULL){
        if(*currentnode->item < MinItem){
            MinItem = *currentnode->item;
        }
        currentnode = currentnode->next;
    }

    *item = MinItem;

    return TRUE;
}

// Removes all duplicate items from a list.
void list_clean(list_linked *source) {
    if(source == NULL || source->front == NULL){
        return;
    }

    list_node *current = source->front;

    while (current != NULL && current->next != NULL) {
        list_node *tracker = current;
        while (tracker->next != NULL) {
            if (*current->item == *tracker->next->item) {
                list_node *duplicate = tracker->next;
                tracker->next = duplicate->next;

                if (duplicate == source->rear) {
                    source->rear = tracker;
                }

                free(duplicate->item);
                free(duplicate);
                source->count--;
            } else {
                tracker = tracker->next;
            }
        }
        current = current->next;
    }
}

// Compares two lists for equality.
BOOLEAN list_equal(const list_linked *target, const list_linked *source) {
    if ((target == NULL && source != NULL) || (target != NULL && source == NULL)) {
        return FALSE;
    }

    if (target == NULL && source == NULL) {
        return TRUE;
    }

    if (target->count != source->count) {
        return FALSE;
    }

    //now if those checks are passed then check for same items inside
    list_node *Target_Track = target->front;
    list_node *Source_Track = source->front;

    while(Target_Track != NULL && Source_Track != NULL){
        if(*Target_Track->item != *Source_Track->item){
            return FALSE;
        }
        Target_Track = Target_Track->next;
        Source_Track = Source_Track->next;
    }

    return TRUE;
}

void list_combine(list_linked *target, list_linked *source1, list_linked *source2) {

    list_node *SourceCurrent = source1->front;
    list_node *SourceCurrentTwo = source2->front;
    BOOLEAN toggle = TRUE;

    while(SourceCurrent != NULL || SourceCurrentTwo != NULL){
        if (toggle && SourceCurrent != NULL) {
            list_node *SourceCurrentNext = SourceCurrent->next;
            SourceCurrent->next = NULL;
            if(target->count == 0){
                target->front = SourceCurrent;
                target->rear = SourceCurrent;
            }else{
                target->rear->next = SourceCurrent;
                target->rear = SourceCurrent;
            }
            target->count++;
            SourceCurrent = SourceCurrentNext;
        } else if (!toggle && SourceCurrentTwo != NULL) {
            list_node *SourceCurrentTwoNext = SourceCurrentTwo->next;
            SourceCurrentTwo->next = NULL;
            if(target->count == 0){
                target->front = SourceCurrentTwo;
                target->rear = SourceCurrentTwo;
            }else{
                target->rear->next = SourceCurrentTwo;
                target->rear = SourceCurrentTwo;
            }
            target->count++;
            SourceCurrentTwo = SourceCurrentTwoNext;
        }
        toggle = !toggle;
    }

    source1->front = NULL;
    source1->rear = NULL;
    source1->count = 0;

    source2->front = NULL;
    source2->rear = NULL;
    source2->count = 0;
    return;
}

void list_split_alt(list_linked *target1, list_linked *target2, list_linked *source) {
    if(source == NULL || source->front == NULL){
        return;
    }

    BOOLEAN isleft = TRUE;
    list_node *CurrentNode = source->front;

    while(CurrentNode != NULL){
        list_node *NextNode = CurrentNode->next;
        CurrentNode->next = NULL;
        if(isleft){
            if(target1->count == 0){
                target1->front = CurrentNode;
                target1->rear = CurrentNode;
            }else{
                target1->rear->next = CurrentNode;
                target1->rear = CurrentNode;
            }
            target1->count++;
        }else{
            if(target2->count == 0){
                target2->front = CurrentNode;
                target2->rear = CurrentNode;
            }else{
                target2->rear->next = CurrentNode;
                target2->rear = CurrentNode;
            }
            target2->count++;
        }
        isleft = !isleft;
        CurrentNode = NextNode;
    }

    source->front = NULL;
    source->rear = NULL;
    source->count = 0;
    return;
}

void list_split(list_linked *target1, list_linked *target2, list_linked *source) {
    if(source == NULL || source->front == NULL){
        return;
    }

    int middle = (source->count + 1) / 2;
    list_node *CurrentNode = source->front;
    for(int i = 0; i < middle; ++i){
        list_node *NextNode = CurrentNode->next;
        CurrentNode->next = NULL;
        if(target1->count == 0){
            target1->front = CurrentNode;
            target1->rear = CurrentNode;
        }else{
            target1->rear->next = CurrentNode;
            target1->rear = CurrentNode;
        }
        target1->count++;
        CurrentNode = NextNode;
    }

    while(CurrentNode != NULL){
        list_node *NextNode = CurrentNode->next;
        CurrentNode->next = NULL;
        if(target2->count == 0){
            target2->front = CurrentNode;
            target2->rear = CurrentNode;
        }else{
            target2->rear->next = CurrentNode;
            target2->rear = CurrentNode;
        }
        target2->count++;
        CurrentNode = NextNode;
    }

    source->front = NULL;
    source->rear = NULL;
    source->count = 0;
    return;
}

void list_split_key(list_linked *target1, list_linked *target2, list_linked *source, data_ptr key) {
    if (source == NULL || source->front == NULL){
        return;
    }

    list_node *CurrentNode = source->front;

    while(CurrentNode != NULL){
        list_node *NextCurrent = CurrentNode->next;
        CurrentNode->next = NULL;

        if(data_compare(CurrentNode->item, key) < 0){
            if(target1->count == 0){
                target1->front = CurrentNode;
                target1->rear = CurrentNode;
            }else{
                target1->rear->next = CurrentNode;
                target1->rear = CurrentNode;
            }
            target1->count++;
        }else if(data_compare(CurrentNode->item, key) >= 0){
            if(target2->count == 0){
                target2->front = CurrentNode;
                target2->rear = CurrentNode;
            }else{
                target2->rear->next = CurrentNode;
                target2->rear = CurrentNode;
            }
            target2->count++;
        }

        CurrentNode = NextCurrent;
    }

    source->front = NULL;
    source->rear = NULL;
    source->count = 0;
    return;
}

list_linked* list_copy(const list_linked *source) {
    if (source == NULL || source->front == NULL) {
        return NULL;
    }

    list_linked *NewList = malloc(sizeof(list_linked));
    if (NewList == NULL) {
        return NULL;
    }

    NewList->front = NULL;
    NewList->rear = NULL;
    NewList->count = 0;

    list_node *current = source->front;

    while (current != NULL) {
        list_node *newNode = malloc(sizeof(list_node));
        if (newNode == NULL) {
            list_free(&NewList);
            return NULL;
        }

        newNode->item = malloc(sizeof(int));
        if (newNode->item == NULL) {
            free(newNode);
            list_free(&NewList);
            return NULL;
        }

        *newNode->item = *current->item;
        newNode->next = NULL;

        if (NewList->count == 0) {
            NewList->front = newNode;
            NewList->rear = newNode;
        } else {
            NewList->rear->next = newNode;
            NewList->rear = newNode;
        }

        NewList->count++;
        current = current->next;
    }

    return NewList;
}

// Prints the items in a list from front to rear.
void list_print(const list_linked *source) {
    char string[DATA_STRING_SIZE];
    list_node *curr = source->front;

    while(curr != NULL) {
        printf("%s\n", data_string(string, sizeof string, curr->item));
        curr = curr->next;
    }
    return;
}
