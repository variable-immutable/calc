#include <stdlib.h>
#include <stdio.h>
#include "stack.h"


stack_t *stack_init() {
    stack_t *stack = malloc(sizeof(stack_t));
    stack->size = 0;
    return stack;
}

void stack_push(stack_t *stack, char ch) {
    stack->top = realloc(stack->top, sizeof(char) + sizeof(char) * stack->size);
    stack->top[stack->size] = ch;
    stack->size++;
}


char stack_pop(stack_t *stack) {
    if(stack->size) {
        stack->size--;
        return stack->top[stack->size];
    }

    return 0;
}

bool stack_is_empty(stack_t *stack) {
    if(stack->size == 0) {
        return true;
    }
    return false;
}

char stack_peek(stack_t *stack) {
    if(stack_is_empty(stack)) {
        return 0;
    }
    return stack->top[stack->size - 1];
}

void stack_print(stack_t *stack) {
    size_t i;
    for(i = 0; i != stack->size; i++) {
        printf("%c", stack->top[i]);
    }
}

void stack_free(stack_t *stack) {
    free(stack->top);
    free(stack);
}
