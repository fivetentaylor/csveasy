#ifndef LIST_H_
#define LIST_H_

#define EMPTYLIST 1
#define HEAD 0
#define TAIL -1

typedef struct node {
    struct node *next;
    struct node *prev;
    void *data;
} node;

typedef struct list {
    unsigned int size;
    node *head;
} list;

int init(list*);

// Return the correct index given a list
// of a certain size and an index using
// modular arithmetic
int safe_index(int, int);

// Push new data on the head of a list
void push(list*, void*);

// Pop data off the end of a list
int pop(list*, void**);

// Remove all elements from a list
int empty(list*);

#endif // LIST_H_
