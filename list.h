#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdio.h>

typedef struct list_item {
    char val;
    struct list_item *next;
} list_item_t;

typedef struct list {
    list_item_t *head;
    list_item_t *tail;
    size_t size;
} list_t;

typedef struct list_iter {
    list_item_t *curr;
} list_iter_t;

list_t *list_init();

void list_push(list_t *list, char ch);

list_iter_t *list_get_iter(list_t *list);

char list_iter_next(list_iter_t *iter);

void list_iter_free(list_iter_t *iter);

void list_print(list_t *list);

char list_peek_back(list_t *list);

void _list_items_free(list_t *list);

void list_clear(list_t *list);

void list_free(list_t *list);

#endif 
