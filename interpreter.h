#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "memory.h"
#include "stack.h"
#include "cell.h"
#include "function_list.h"

int launcher(char* input);
int interpreter(char* input, struct cell*** memory, 
        char* registers, int std_in_index, int index,
        int* func_args, struct tuple position);
struct flist* function_dec(char* input, int* index,
        struct flist* list, int val);

#endif // INTERPRETER_H
