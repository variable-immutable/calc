#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"


stack_t *stack_init(size_t type_size) {
    stack_t *stack = malloc(sizeof(stack_t));
    stack->size = 0;
    stack->type_size = type_size;
    return stack;
}

void stack_push(stack_t *stack, void *val) {
    stack->top = realloc(stack->top, sizeof(stack->type_size) + sizeof(stack->type_size) * stack->size);
    memcpy(stack->top + (stack->type_size * stack->size), val, stack->type_size);
    stack->size++;
}


void *stack_pop(stack_t *stack) {
    if(stack->size) {
        stack->size--;
        return stack->top + stack->type_size * stack->size;
    }

    return NULL;
}

bool stack_is_empty(stack_t *stack) {
    if(stack->size == 0) {
        return true;
    }
    return false;
}

bool stack_peek(stack_t *stack, void *ret) {
    if(stack_is_empty(stack)) {
        return false;
    }

    memcpy(ret, stack->top + stack->type_size * (stack->size - 1), stack->type_size);
    return true;
}

void stack_free(stack_t *stack) {
    free(stack->top);
    free(stack);
}
