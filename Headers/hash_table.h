#ifndef HASH_TABLE_H
#define HASH_TABLE_H

/**
 * @file hash_table.h
 * @brief Hash table implementation for storing and managing key-value pairs.
 *
 * This file contains the function declarations and type definitions needed to
 * manage a simple hash table. The hash table uses an array of linked lists to handle
 * collisions efficiently.
 */

#include "globals.h"
#include "linked_list.h"

/* Type definition for the hash table structure */
typedef Node hash_table[TABLE_SIZE];

/**
 * @brief Generates a hash value for a given key using the djb2 algorithm.
 *
 * This function computes a hash value based on the input key, which is then
 * adjusted to fit within the bounds of the table size.
 *
 * @param key The string key to hash.
 * @return The hash value as an unsigned int.
 */
unsigned int hash(const char* key);

/**
 * @brief Inserts a key-value pair into the hash table.
 *
 * This function calculates the appropriate index using the hash function and
 * inserts the key-value pair into the linked list at that index.
 *
 * @param table The hash table into which the key-value pair will be inserted.
 * @param key The key to insert into the table.
 * @param value A pointer to the value associated with the key.
 */
void insert_table(hash_table table, char* key, void* value);

/**
 * @brief Searches for a value in the hash table using a key.
 *
 * This function looks up the value associated with the specified key in the
 * hash table. If the key is found, the corresponding value is returned.
 *
 * @param table The hash table to search.
 * @param key The key to search for in the table.
 * @return A pointer to the value associated with the key, or NULL if the key is not found.
 */
void* search_table(hash_table table, char* key);

/**
 * @brief Checks if a key exists in the hash table.
 *
 * This function verifies whether a specific key is present in the hash table.
 *
 * @param table The hash table to check.
 * @param key The key to look for in the table.
 * @return 1 if the key is found, 0 otherwise.
 */
int is_in_table(hash_table table, char* key);

/**
 * @brief Prints all key-value pairs in the hash table.
 *
 * This function iterates through the hash table and prints the keys and values
 * stored in each bucket. The output is formatted for easy reading.
 *
 * @param table The hash table to print.
 */
void print_table(hash_table table);

/**
 * @brief Frees all memory allocated for the hash table.
 *
 * This function releases the memory used by the linked lists in each bucket of the
 * hash table, effectively cleaning up all resources associated with the table.
 *
 * @param table The hash table to free.
 */
void free_table(hash_table table);

#endif /* MACRO_TABLE_H */
