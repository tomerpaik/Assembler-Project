#include "linked_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Node {
    char *key; /* Line identifier */
    void *value; /* Line data */
    struct Node* next;
};

Node create_node(char *key, void *value) {
    Node new;
    new = (Node)malloc(sizeof(struct Node));

    if (new == NULL) {
        fprintf(stderr, "Node Memory allocation failed\n");
        exit(1);
    }

    new->key = key;
    new->value = value;
    new->next = NULL;

    return new;
}

void addLine(Node const source, const char *line) {
    Node current = source;
    Node new_node;
    char *line_copy;
    line_copy = (char *)malloc(strlen(line) + 1);
    if (line_copy == NULL) {
        printf( "Line Memory allocation failed\n");
        exit(1);
    }
    strcpy(line_copy, line);
    new_node = create_node("", (void *)(line_copy));

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_node;
}

void *get_value(Node const source) {
    return source->value;
}
Node get_next(Node const source) {
    return source->next;
}
void set_next(Node const source, Node const next) {
    source->next = next;
}

void printList(Node const source) {
    int i;
    Node current = source->next; /*skeep the first */

    i=1;
    while (current != NULL) {
        printf("Key: %s, Value: %s\n", current->key, (char*)(get_value(current)));
        current = current->next;
        i++;
    }
}

void freeList(Node const head) {
    Node current = head;
    Node next;

    while (current != NULL) {
        next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
}

