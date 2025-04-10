#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>

/**
 * @file table.h
 * @brief Hash table implementation with separate chaining using linked lists.
 *
 * Description: 
 *    [Add a short description of the purpose of this module]
 *
 * Usage:
 *    [Example usage or basic instructions]
 *
 * Author: [Your Name]
 * Date: [Date]
 */

#define DEFAULT_TABLE_SIZE 10
#define DEFAULT_SEED 5381
#define DEFAULT_MULTIPLIER 5

// Structs

/**
 * @brief Key-value pair stored in the table.
 */
typedef struct TableVal {
    int address;
    char* val;
    char* key;
} TableVal;

/**
 * @brief Node for the linked list used in separate chaining.
 */
typedef struct Node {
    TableVal val;
    struct Node* next;
} Node;

/**
 * @brief Table is an array of Node pointers.
 */
typedef Node** Table;

// Linked list functions

/**
 * @brief Creates a new linked list node with the given TableVal.
 * @param val The TableVal to store in the node.
 * @return Pointer to the newly created node.
 */
Node* create_node(TableVal val);

/**
 * @brief Adds a new node with the given TableVal to the end of the linked list.
 * @param head The head of the linked list.
 * @param val The TableVal to add.
 */
void add_node(Node* head, TableVal val);

/**
 * @brief Retrieves the value associated with a key in the linked list.
 * @param head The head of the linked list.
 * @param key The key to search for.
 * @return The value associated with the key, or an empty string if not found.
 */
const char* ll_get(Node* head, const char* key);

/**
 * @brief frees the memory allocated to the linked list
 * @param head the head of the linked list.
 */
void ll_free(Node* head);
/**
 * @brief Hashes a string using the djb2 algorithm.
 * @param str The input string to hash.
 * @return The computed hash.
 */
unsigned long djb2_hash(const char *str);

/**
 * @brief Creates and initializes a new hash table.
 * @return A new Table with all buckets initialized to NULL.
 */
Table create_table();

/**
 * @brief Adds a key-value pair to the hash table.
 * @param t The hash table.
 * @param key The key string.
 * @param val The value string. for the symbol tables this will be where the type of symbol is stored.
 * @param address The address associated with the code. 
 */
void table_add(Table t, char* key, char* val, int address);

/**
 * @brief Retrieves the value associated with a key in the hash table.
 * @param t The hash table.
 * @param key The key string.
 
 * @return The value associated with the key, or an empty string if not found.
 */
const char* table_get(Table t, const char* key);

#endif // TABLE_H

