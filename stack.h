#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdbool.h>

typedef struct stack {
    void *top;
    size_t size;
    size_t type_size;
} stack_t;

stack_t *stack_init(size_t type_size);

void stack_push(stack_t *stack, void *val);

void *stack_pop(stack_t *stack);

bool stack_is_empty(stack_t *stack);

bool stack_peek(stack_t *stack, void *ret);

void stack_free(stack_t *stack);

#endif 
