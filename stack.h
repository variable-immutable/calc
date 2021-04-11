#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdbool.h>

typedef struct stack {
    char *top;
    size_t size;
} stack_t;

stack_t *stack_init();

void stack_push(stack_t *stack, char ch);

char stack_pop(stack_t *stack);

bool stack_is_empty(stack_t *stack);

char stack_peek(stack_t *stack);

void stack_print(stack_t *stack);

void stack_free(stack_t *stack);

#endif 
