#ifndef LINKED_LISTS_H
#define LINKED_LISTS_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "general_functions.h"

struct Node {
    char *key; /* Line identifier */
    void *value; /* Line data */
    struct Node* next;
};

typedef struct Node *Node;

void * search_linked(Node root, char* key);

Node create_node(char *key, void *value);
void insert_node(Node * root, char *key, void *value);
void *get_value(Node source);
Node get_next(Node source);
void set_next(Node source, Node next);
void printList(Node source);
void freeList(Node head);

#endif /* LINKED_LISTS_H */
