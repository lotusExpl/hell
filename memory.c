#include "memory.h"

#include <stdlib.h>
#include <stdio.h>

//init a single array for the memory
struct cell** init_array(unsigned int size) {
    struct cell** array = calloc(size, sizeof(struct cell*));
    for (int i = 0; i < size; i++) {
        array[i] = init_cell(0, 0);
    }
    return array;
}

// init an entire grid for the 2D memory
struct cell*** init_grid(unsigned int sizeX, unsigned int sizeY){
    struct cell*** memory = calloc(sizeY, sizeof(struct cell**));
    for (int i = 0; i < sizeY; i++) {
        memory[i] = init_array(sizeX);
    }
    return memory;
}

void free_cell_array(struct cell** array, int sizeX) {
    for (int i = 0; i < sizeX; i++) {
        free(array[i]);
    }
    free(array);
}

// function to free the entire memory
void free_memory(struct cell*** memory, int sizeY, int sizeX) {
    for (int i = 0; i < sizeY; i++) {
        free_cell_array(memory[i], sizeX);
    }
    free(memory);
}

//debug func to print a specific line of the memory as digits
void memory_line_print_d(struct cell*** memory, int line, int sizeX) {
    printf("[ %.3d", memory[line][0]->curr);
    for (int i = 1; i < sizeX; i++) {
        printf(", %.3d", memory[line][i]->curr);
    }
    printf(" ]\n");
}
