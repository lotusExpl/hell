#ifndef STACK_H_
#define STACK_H_

#include <stddef.h>

struct stack{
    struct stack* next;
    size_t index;
};


struct stack* push(struct stack *stak, size_t value);

struct stack* pop(struct stack *stak);

struct stack* init();

void print_stack(struct stack* stak);

void free_stack(struct stack* stak);

#endif
