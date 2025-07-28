#include "stack.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct stack*  push(struct stack *stak, size_t value){
    struct stack *tmp = malloc(sizeof(struct stack));
    tmp->index = value;
    tmp->next = stak;
    return tmp;
}

struct stack* pop(struct stack *stak){
    struct stack *tmp = stak;
    stak = stak->next;
    return tmp;
}

struct stack* init(){
    struct stack *new = malloc(sizeof(struct stack));
    new->index = 0;
    new->next = NULL;
    return new;
}

void print_stack(struct stack* tmp){
    printf("\n");
    struct stack* stak = tmp;
    while(stak->next != NULL){
        printf("%4ld",stak->index);
        stak = stak->next;
    }
}

void free_stack(struct stack* stak){
    if (stak == NULL) {
        return;
    }
    struct stack* tmp = stak;
    while(tmp->next != NULL){
        tmp = stak->next;
        free(stak);
        stak = tmp;
    }
    free(tmp);
}
