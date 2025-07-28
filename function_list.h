#ifndef FUNCTION_LIST_H
#define FUNCTION_LIST_H

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include "cell.h"

// use NULL to initialize a flist without values
struct flist {
    int val; // value associated to the function
    int index;
    int count;
    struct flist* next;
};

struct tuple {
    int a;
    int b;
};

struct flist* flist_push(struct flist* list, int val, 
        int index, int count);
int flist_is_present(struct flist* list, int val);
struct flist* flist_update(struct flist* list, 
        int val, int index, int count);
struct flist* flist_add(struct flist* list, 
        int val, int index, int count);
struct flist* flist_delete(struct flist* list, int val);
void flist_destroy(struct flist* el);
void flist_free(struct flist* list);
void flist_print_el(char* input, struct flist* el);
int* compute_args(int val, int index, char* input,
        int* registers, int* func_args, struct tuple position);
struct tuple exec_func(char* input, struct cell*** memory, 
        struct tuple position, int val, int* func_args,
        int* REGISTERS, int std_in_index, int INDEX);

#endif // FUNCTION_LIST_H
