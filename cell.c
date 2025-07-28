#include "cell.h"

#include <stdlib.h>

struct cell* init_cell(int c, int o) {
    struct cell* res = calloc(1, sizeof(struct cell));
    res->curr = c;
    res->old = o;
    return res;
}

int cell_minus(struct cell* cell) {
    cell->old = cell->curr;
    //cell->curr = (cell->curr - 1 + 255) % 255;
    if (cell->curr == 0) {
        cell->curr = 255;
    } else {
        cell->curr--;
    }
    return cell->curr;
}

int cell_plus(struct cell* cell) {
    cell->old = cell->curr;
    //cell->curr = (cell->curr + 1 + 255) % 255;
    if (cell->curr == 255) {
        cell->curr = 0;
    } else {
        cell->curr++;
    }
    return cell->curr;
}

// update the curr value of a cell with a given value
int cell_update(struct cell* cell, int value) {
    cell->old = cell->curr;
    cell->curr = value;
    return cell->curr;
}

// swaps old and curr states of the cell and return old state
// works kind of like cd -
int cell_change_state(struct cell* cell) {
    int tmp = cell->curr;
    cell->curr = cell->old;
    cell->old = tmp;
    return cell->curr;
}

void cell_print(struct cell* cell) {
    printf("( curr: %d, old: %d )\n", cell->curr, cell->old);
}

void cell_print_char(struct cell* cell) {
    printf("( curr: %c, old: %c )\n", cell->curr, cell->old);
}
