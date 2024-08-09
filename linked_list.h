#ifndef LINKED_LISTS_H
#define LINKED_LISTS_H

#define MAX_LINE_LENGTH 82


typedef struct Node *Node;
Node create_node(char *key, void *value);
void addLine(Node const source, const char *line);
void *get_value(Node source);
Node get_next(Node source);
void set_next(Node source, Node next);
void printList(Node source);
void freeList(Node head);

#endif /* LINKED_LISTS_H */
