#ifndef CELL_H
#define CELL_H

#include <stdio.h>

struct cell {
    int curr;
    int old;
};

int cell_minus(struct cell* cell);
int cell_plus(struct cell* cell);
int cell_update(struct cell* cell, int value);
int cell_change_state(struct cell* cell);

void cell_print(struct cell* cell);
void cell_print_char(struct cell* cell);

struct cell* init_cell(int c, int o);

#endif // CELL_H
