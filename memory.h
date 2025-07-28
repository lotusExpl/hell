#ifndef MEMORY_H
#define MEMORY_H

#include "cell.h"

struct cell** init_array(unsigned int size);
struct cell*** init_grid(unsigned int sizeX, unsigned int sizeY);
void free_cell_array(struct cell** array, int sizeX);
void free_memory(struct cell*** memoryi, int sizeY, int sizeX);

void memory_line_print_d(struct cell*** memory, int line, int sizeX);

#endif // MEMORY_H
