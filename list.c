#include <stdlib.h>
#include "list.h"

list_t *list_init() {
    list_t *list = malloc(sizeof(list_t));
    list->size = 0;
    return list;
}

void list_push(list_t *list, char ch) {
    list_item_t *curr_item = malloc(sizeof(list_item_t));
    curr_item->val = ch;

    if(list->head) {
        list->tail->next = curr_item;
    } else {
        list->head = curr_item;
    }
    list->size++;
    list->tail = curr_item;
}


list_iter_t *list_get_iter(list_t *list) {
    list_iter_t *iter = malloc(sizeof(list_iter_t));
    iter->curr = list->head;
    return iter;
}

char list_iter_next(list_iter_t *iter) {
    if(!iter->curr) {
        return 0;
    }

    char ch = iter->curr->val;
    iter->curr = iter->curr->next;
    return ch;
}

void list_iter_free(list_iter_t *iter) {
    free(iter);
}

void list_print(list_t *list) {
    if(!list->head) return;

    char ch;
    list_iter_t *iter = list_get_iter(list);

    while((ch = list_iter_next(iter))) {
        printf("%c", ch);
    }

    list_iter_free(iter);
}

char list_peek_back(list_t *list) {
    if(!list->tail) {
        return 0;
    }

    return list->tail->val;
}

void _list_items_free(list_t *list) {
    list_iter_t *iter = list_get_iter(list);
    list_item_t *curr_item;

    while((curr_item = iter->curr)) {
        iter->curr = iter->curr->next;
        free(curr_item);
    }

    list_iter_free(iter);
}

void list_clear(list_t *list) {
    _list_items_free(list);

    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

void list_free(list_t *list) {
    _list_items_free(list);
    free(list);
}
