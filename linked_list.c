#include "linked_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "general_functions.h"


Node create_node(char *key, void *value) {
    Node new;
    new = (Node)handle_malloc(sizeof(struct Node));

    if (new == NULL) {
        fprintf(stderr, "Node Memory allocation failed\n");
        exit(1);
    }

    new->key = my_strdup(key);
    new->value = my_strdup(value);
    new->next = NULL;

    return new;
}
void insert_node(Node * root, char *key, char *value) {
    Node new_node = create_node(key, value);

    if (*root == NULL) {
        *root = new_node;
    } else {
        Node temp = *root;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}


void * search_linked(Node root, char* key) {
    Node temp = root;
    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            return temp->value;
        }
        temp = temp->next;
    }
    return 0;
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

void freeList(Node root) {
    Node current = root;
    Node next;

    while (current != NULL) {
        next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
}

