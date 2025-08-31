#include "interpreter.h"

int MEMORY_SIZE = 255;

// interprets an input code and create local coordinates etc
int interpreter(char* input, struct cell*** memory,
        char* REGISTERS, int std_in_index, int INDEX,
        int* func_args, struct tuple* position) {
    int X = position->a;      // x axis in memory
    int Y = position->b;      // y axis in memory
    struct stack* loop_stack = NULL;
    struct flist* functions = NULL;

    while (input[INDEX] != '\0') {
        switch (input[INDEX]) {
            case '+':
                cell_plus(memory[Y][X]);
                break;

            case '-':
                cell_minus(memory[Y][X]);
                break;

            case '>':
                X = (X + 1 + MEMORY_SIZE) % MEMORY_SIZE;
                break;

            case '<':
                X = (X - 1 + MEMORY_SIZE) % MEMORY_SIZE;
                break;

            case '^':
                Y = (Y - 1 + MEMORY_SIZE) % MEMORY_SIZE;
                break;

            case '_':
                Y = (Y + 1 + MEMORY_SIZE) % MEMORY_SIZE;
                break;

            case '.':
                //memory_line_print_d(memory, 0, MEMORY_SIZE);
                printf("%c", memory[Y][X]->curr);
                break;

            case '\"':
                printf("%d", memory[Y][X]->curr);
                break;

            case '%':
                cell_change_state(memory[Y][Y]); 
                break;

            case '~':
                cell_update(memory[Y][X], X);
                break;

            case '=':
                cell_update(memory[Y][X], Y);
                break;

            case '`':
                X = memory[Y][X]->curr;
                break;

            case '\'':
                Y = memory[Y][X]->curr;
                break;

            case '@':
                INDEX++;
                if (input[INDEX] == '\0') {
                    printf("Error: Nothing after register asign call.\n");
                    return -1;
                } else if (input[INDEX] < '0' ||
                        input[INDEX] > '7') {
                    printf("Error: Unexpected symbol \"%c\" after register asign call.\n", input[INDEX]);
                    return -1;
                }
                REGISTERS[input[INDEX] - '0'] = memory[Y][X]->curr;
                break;

            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                cell_update(memory[Y][X], REGISTERS[input[INDEX] - '0']);
                break;

            case '[':
                loop_stack = push(loop_stack, INDEX);
                break;

            case ']':
                if (loop_stack == NULL) {
                    printf("Error: Unexpected symbol, closing loop at index %d.\n", INDEX);
                    return -1;
                }
                if (memory[Y][X]->curr != 0) {
                    INDEX = loop_stack->index;
                }
                else{
                    loop_stack = pop(loop_stack);
                }
                break;

            case '{':
                functions = function_dec(input, &INDEX, 
                        functions, memory[Y][X]->curr);
                break;  // here the INDEX has already been updated to 
                        // the end of the function declaration
                        // plus the } is replaced by \0

            case '}':   // should never reach here because the { updates
                        // the INDEX automatically as said above
                        // and replace u with \0
                printf("Error: trailing } at index: %d.\n", INDEX);
                return -1;

            case '(':
                // TODO
                break;
        }
        INDEX++;
    }
    // here I update the position so the outer scope is correctly placed
    // usefull whe this is a function execution that moves the position
    position->a = X;
    position->b = Y;
    flist_free(functions);
    free_stack(loop_stack);
    return 0;
}

// create a new function in the function list
// return the updated flist
// index is given as pointer so it is updated automatically
struct flist* function_dec(char* input, int* index,
        struct flist* list, int val) {

    int char_count = 0;
    (*index)++; // start of the function code
    while (input[(*index) + char_count] != '}') {
        char_count++;
    }
    input[(*index) + char_count] = '\0'; // put a \0 at the end of the dec
                                         // for easier interpretation
    list = flist_add(list, val, *index, char_count);
    *index = *index + char_count;
    return list;
}

int launcher(char* input) {
    int INDEX = 0;  // input index
    MEMORY_SIZE = 255;
    struct cell*** MEMORY = init_grid(MEMORY_SIZE, MEMORY_SIZE);
    char REGISTERS[8] = "01234567";
    struct tuple pos = {0,0};
    int ret_val = interpreter(input, MEMORY, REGISTERS, 0, INDEX, NULL,&pos);
    printf("\n");
    free_memory(MEMORY, MEMORY_SIZE, MEMORY_SIZE);
    return ret_val;
}
