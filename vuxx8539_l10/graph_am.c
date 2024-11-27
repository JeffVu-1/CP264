/**
 * -------------------------------------
 * @file  graph_am.c
 * Adjacency Matrix Graph Code File
 * -------------------------------------
 * @author Jeff Vu, 169058539, vuxx8539@mylaurier.ca
 *
 * @version 2024-03-14
 *
 * -------------------------------------
 */
#include "graph_am.h"

// Initializes an adjacency matrix graph.
graph_am* graph_am_initialize(int size) {
    graph_am *source = malloc(sizeof *source);
    source->size = size;
    // Initialize values to zeroes.
    source->values = calloc(size * size, sizeof *source->values);
    return source;
}

void graph_am_free(graph_am **source) {
    // Free up the data array.
    free((*source)->values);
    (*source)->values = NULL;
    free(*source);
    *source = NULL;
    return;
}

int graph_am_add_vertice(graph_am *source, const graph_am_pair *pair) {
    int added = 0;

    int row = pair->row;
    int col = pair->col;

    if (row == col) {
        source->values[row * source->size + col] = 2;
    }else{
        source->values[row * source->size + col] = 1;
        source->values[col * source->size + row] = 1;
    }

    added++;
    return added;
}

int graph_am_remove_vertice(graph_am *source, const graph_am_pair *pair) {
    int removed = 0;

    int row = pair->row;
    int col = pair->col;

    if (row == col) {
        source->values[row * source->size + col] = 0;
    }else{
        source->values[row * source->size + col] = 0;
        source->values[col * source->size + row] = 0;
    }

    removed++;


    return removed;
}

graph_am* graph_am_create(int size, const graph_am_pair pairs[], int count) {

    graph_am *source = graph_am_initialize(size);
    source->size = size;
    int widthandheight = size * size;
    int *values = (int *)malloc(widthandheight * sizeof(int));

    for(int i = 0; i < widthandheight; i++){
        values[i] = 0;
    }

    source->values = values;
    for(int i = 0; i < count; i++){
        int row = pairs[i].row;
        int col = pairs[i].col;

        if (row == col) {
            source->values[row * source->size + col] = 2;
        }else{
            source->values[row * source->size + col] = 1;
            source->values[col * source->size + row] = 1;
        }

    }

    return source;
}

void graph_am_neighbours(const graph_am *source, int vertex, int vertices[], int *count) {
    if (vertex < 0 ||vertex >= source->size){
        return;
    }

    for(int col = 0; col < source->size; col++){
        if(source->values[vertex * source->size + col] == 1 || source->values[vertex * source->size + col] == 2){
            vertices[*count] = col;
            (*count)++;
        }
    }
}

int graph_am_degree(const graph_am *source, int vertex) {
    int connected = 0;

    if (vertex < 0 || vertex >= source->size) {
        return -1;
    }

    for (int col = 0; col < source->size; col++) {
        if (source->values[vertex * source->size + col] == 2) {
            connected++;
            connected++;
        }else if(source->values[vertex * source->size + col] == 1){
            connected++;
        }
    }

    return connected;
}

void graph_am_breadth_traversal(const graph_am *source, int vertex, int vertices[], int *count) {

    int *visited = (int*)malloc(source->size * sizeof(int));
    for (int i = 0; i < source->size; i++) {
        visited[i] = 0;
    }

    visited[vertex] = 1;

    int *currentLevel = (int*)malloc(source->size * sizeof(int));
    int levelStart = 0;
    int levelEnd = 0;

    currentLevel[levelEnd++] = vertex;

    *count = 0;

    while (levelStart < levelEnd) {
        int current_vertex = currentLevel[levelStart++];
        vertices[*count] = current_vertex;
        (*count)++;
        for (int col = 0; col < source->size; col++) {
            if (source->values[current_vertex * source->size + col] == 1 && !visited[col]) {
                visited[col] = 1;
                currentLevel[levelEnd++] = col;
            }
        }
    }

    free(visited);
    free(currentLevel);
}

void graph_am_depth_traversal(const graph_am *source, int vertex, int vertices[], int *count) {

    int *visited = (int*)malloc(source->size * sizeof(int));
	for (int i = 0; i < source->size; i++) {
		visited[i] = 0;
	}


    int *stack = (int*)malloc(source->size * sizeof(int));
	int top = 0;
	stack[top] = vertex;
	*count = 0; // need this to keep track the size of the verticies array but also to ensure each item is pushed on properly at the right index
	while (top >= 0) {
		int current = stack[top--]; // grabbing the vertex then subtract 1 from the stack
		if (!visited[current]) { // check if this vertex has been visited and if it hasn't continue
			vertices[(*count)++] = current; // push the current vertex into the array
			visited[current] = 1; // mark it as visited
			for (int col = 0; col < source->size; col++) { // add all the adjacete values
            //current is equal to vertex in this case, if the opposite is greater than 1 and it's not visited then we add that to the stack
				if (source->values[col * source->size + current] > 0 && !visited[col]) {
					stack[++top] = col;
				}
			}
		}
	}
}

// Prints the contents of an adjacency matrix graph.
void graph_am_print(const graph_am *source) {
    // Print the column numbers.
    printf("    ");

    for(int i = 0; i < source->size; i++)
        printf("%3d", i);
    printf("\n");
    printf("    ");
    for(int i = 0; i < source->size; i++)
        printf("---");
    printf("\n");

    // Print the row numbers and rows.
    for(int i = 0; i < source->size; i++) {
        printf("%3d|", i);

        for(int j = 0; j < source->size; j++) {
            // find item using offsets
            printf("%3d", *(source->values + i * source->size + j));
        }
        printf("\n");
    }
}
