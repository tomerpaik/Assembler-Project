#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/**
 * @file linked_list.h
 * @brief Linked list implementation for storing key-value pairs.
 *
 * This file contains the function declarations and type definitions needed to
 * manage a simple singly linked list. Each node in the list contains a key-value
 * pair and a pointer to the next node.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "general_functions.h"

/* Structure defining a node in the linked list */
struct Node {
    char *key;         /**< Key associated with the node */
    void *value;       /**< Value associated with the key */
    struct Node* next; /**< Pointer to the next node in the list */
};

typedef struct Node *Node;

/**
 * @brief Searches for a key in a linked list.
 *
 * This function traverses the linked list to find a node with the specified key.
 * If the key is found, it returns the associated value.
 *
 * @param root The root node of the linked list.
 * @param key The key to search for.
 * @return A pointer to the value associated with the key, or NULL if the key is not found.
 */
void * search_linked(Node root, char* key);

/**
 * @brief Creates a new node with the specified key and value.
 *
 * This function allocates memory for a new node, assigns the key and value, and
 * initializes the next pointer to NULL.
 *
 * @param key The key for the new node.
 * @param value The value associated with the key.
 * @return A pointer to the newly created node.
 */
Node create_node(char *key, void *value);

/**
 * @brief Inserts a new node into the linked list.
 *
 * This function creates a new node and inserts it at the end of the linked list.
 * If the list is empty, the new node becomes the root.
 *
 * @param root The root node of the linked list (passed by reference).
 * @param key The key for the new node.
 * @param value The value associated with the key.
 */
void insert_node(Node * root, char *key, void *value);

/**
 * @brief Retrieves the value stored in a node.
 *
 * This function returns the value stored in the specified node.
 *
 * @param source The node from which to retrieve the value.
 * @return A pointer to the value stored in the node.
 */
void *get_value(Node source);

/**
 * @brief Gets the next node in the linked list.
 *
 * This function returns the pointer to the next node in the linked list.
 *
 * @param source The node whose next pointer is to be retrieved.
 * @return The next node in the linked list.
 */
Node get_next(Node source);

/**
 * @brief Sets the next node in the linked list.
 *
 * This function updates the next pointer of the specified node to point to the given node.
 *
 * @param source The node whose next pointer is to be set.
 * @param next The node to set as the next node.
 */
void set_next(Node source, Node next);

/**
 * @brief Prints all nodes in the linked list.
 *
 * This function traverses the linked list and prints the key-value pairs stored in each node.
 *
 * @param source The root node of the linked list.
 */
void printList(Node source);

/**
 * @brief Frees all memory associated with the linked list.
 *
 * This function releases the memory used by each node in the linked list,
 * including the keys, values, and nodes themselves.
 *
 * @param head The root node of the linked list.
 */
void freeList(Node head);



#endif /* LINKED_LISTS_H */
