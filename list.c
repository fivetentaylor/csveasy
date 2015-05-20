#include <stdlib.h>
#include "list.h"

int init(list* l) {
    l->size = 0;
    return 0;
}

int safe_index( int size, int index ) {
    div_t d = div(index, size);
    return 0;
}

void push(list* l, void* data) {
    node* new = malloc(sizeof(node));
    if( l->size ) {
        new->next = l->head;
        new->prev = l->head->prev;
    } else {
        new->next = new;
        new->prev = new;
    }
    new->data = data;
    l->head = new;
    l->size++;
}

int pop(list* l, void** data) {
    if( l->size ) {
        return 1;
    } else {
        return EMPTYLIST;
    }
    return 0;
}

int empty(list* l) {
    return 0;
}


