#include "function_list.h"

// push the new function in front, use the return value to update you list
struct flist* flist_push(struct flist* list, int val, 
        int index, int count) {
    struct flist* res = calloc(1, sizeof(struct flist));
    res->count = count;
    res->index = index;
    res->val = val;
    res->next = list;
    return res;
}

// return 1 if the given vaue is already associated to a function
// else return 0
int flist_is_present(struct flist* list, int val) {
    while (list != NULL) {
        if (list->val == val) {
            return 1;
        }
        list = list->next;
    }
    return 0;
}

// update the function associated to the given value to the new code
// return the list updated
struct flist* flist_update(struct flist* list, 
        int val, int index, int count) {
    struct flist* init = list;
    while (list != NULL) {
        if (list->val == val) {
            list->count = count;
            list->index = index;
            return init;
        }
        list = list->next;
    }
    return init;
}

// function that updates the list or push a new function if 
// val is not present in the list already
// return a pointer to the updated list
struct flist* flist_add(struct flist* list, 
        int val, int index, int count) {
    if (flist_is_present(list, val) == 1) {
        list = flist_update(list, val, index, count);
    } else {
        list = flist_push(list, val, index, count);
    }
    return list;
}

// return the list with the deleted element if its found
struct flist* flist_delete(struct flist* list, int val) {
    struct flist* tmp = list->next;

    if (list->val == val) {
        flist_destroy(list);
        return tmp;
    }

    struct flist* init = list;

    while (tmp != NULL) {
        if (tmp->val == val) {
            list->next = tmp->next;
            flist_destroy(tmp);
            return init;
        }
        list = tmp;
        tmp = tmp->next;
    }
    return init;
}

// free an flist element not the entire list
void flist_destroy(struct flist* el) {
    free(el);
}

// recursively frees the entire function list
void flist_free(struct flist* list) {
    if (list != NULL) {
        flist_free(list->next);
        flist_destroy(list);
    }
}

// prints a single element of the function_list
void flist_print_el(char* input, struct flist* el) {
    if (el == NULL) {
        printf("flist_print_el: el is NULL.\n");
        return;
    }
    printf("function(%d):(index: %d, count: %d)\ncode: ",
            el->val, el->index, el->count);
    for (int i = el->index; i < el->index + el->count; i++) {
        printf("%c", input[i]);
    }
    printf("\n");
}

// computes the arguments in the function call
// can only take |+-=~ macro calls, and function args
int* compute_args(int val, int index, char* input,
        int* registers, int* func_args, struct tuple* position) {
    int * res = calloc(9, sizeof(int));
    res[0] = val;
    int i = 1;
    while (input[index] != ')') {
        switch (input[index]) {
            case '|':
                i++;
                if (i == 8) {
                    printf("Error: function call with to many args.\n");
                    return NULL;
                }
                break;

            case '+':
                if (res[i] == 255) {
                    res [i] = 0;
                    break;
                }
                res[i]++;
                break;

            case '-':
                if (res[i] == 0) {
                    res [i] = 255;
                    break;
                }
                res[i]--;
                break;

            case '$':
                if (func_args == NULL) {
                    printf("Error: Usage of function args in the main process.\n");
                    return NULL;
                }
                index++;
                if (input[index] < '0' || input[index] > '7') {
                    printf("Error: Bad argument call in a function call, wrong symbol after $.\n");
                    return NULL;
                }
                res[i] = func_args[input[index] - '0'];
                break;

            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                res[i] = registers[input[index] - '0'];
                break;

            case '~':
                res[i] = position->a;
                break;

            case '=':
                res[i] = position->b;
                break;
            // TODO add the macro calls maybe

            default:
                printf("Error: unexpected symbols in function call.\n");
                return NULL;
        }
        index++;
    }
    return res;
}

// return the new position I guess
// here func_args is the possible args of the current scope 
// if this call is already made in a function
// but the execution is made with new args 
/*
struct tuple exec_func(char* input, struct cell*** memory, 
        struct tuple* position, int val, int* func_args,
        int* REGISTERS, int std_in_index, int INDEX) {

    int* new_args = compute_args(val, INDEX, input, 
            REGISTERS, func_args, position);
    // should init the args for the function execution in a new scope
    int exec_res = interpreter(input, cell*** memory,
        REGISTERS, std_in_index, 0, // this is the new index ,
        new_args, position);

    return *position;
}
*/
// remarks
/*
    std_in_index should be a pointer so its state is saved through scopes
   */
