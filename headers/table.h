#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>

/**
 * @file table.h
 * @brief Hash table implementation with separate chaining using linked lists.
 *
 * This module implements a hash table with separate chaining using linked lists to handle collisions.
 * The table is used to store key-value pairs, where the keys are strings, and the values are associated 
 * with specific data, like addresses and symbols.
 *
 * the linked lists are given a struct called TableVal as their val which contains two strings and ints which are used in various 
 * ways inside the assembler.
 *
 *
 * Author: Ilan Kayesar
 * Date: 2.4.25
 */

#define DEFAULT_TABLE_SIZE 10      /**< Default size of the hash table */
#define DEFAULT_SEED 5381          /**< Seed value for the djb2 hash function */
#define DEFAULT_MULTIPLIER 5       /**< Multiplier used in the djb2 hash function */

/** Structs*/

/**
 * @brief Key-value pair stored in the table.
 */
typedef struct TableVal {
    int address;  /** Address associated with the symbol */
    char* val;    /** Value associated with the key (e.g., symbol type) */
    char* key;    /** Key used to identify the entry (e.g., symbol name) */
    int line_num;
} TableVal;

/**
 * @brief Node for the linked list used in separate chaining.
 */
typedef struct Node {
    TableVal val;        /**< The key-value pair */
    struct Node* next;   /**< Pointer to the next node in the linked list */
} Node;

/**
 * @brief Table is an array of Node pointers.
 */
typedef Node** Table;

/** Linked list functions*/

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
 * @brief Retrieves the address associated with a key in the linked list.
 * @param head The head of the linked list.
 * @param key The key to search for.
 * @return The address associated with the key, or -1 if not found.
 */
int ll_get_address(Node* head, const char* key);

/**
 * @brief Frees the memory allocated to the linked list.
 * @param head The head of the linked list.
 */
void ll_free(Node* head);

/**
 * @brief Adds an offset to the address of each node in the linked list.
 * @param head The head of the linked list.
 * @param n The offset to add to the address.
 */
void ll_add_address(Node* head, int n);

/** Hash table functions*/

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
 * @param val The value string (e.g., symbol type).
 * @param address The address associated with the code or symbol.
 */
int table_add(Table t, char* key, char* val, int address);

/**
 * @brief Adds a key-value pair to the hash table with a line number as well.
 * @param t The hash table.
 * @param key The key string.
 * @param val The value string (e.g., symbol type).
 * @param address The address associated with the code or symbol.
 * @param line_num
 */
int table_add_line_number(Table t, char* key, char* val, int address,int line_num);
/**
 * @brief Retrieves the value associated with a key in the hash table.
 * @param t The hash table.
 * @param key The key string.
 * @return The value associated with the key, or an empty string if not found.
 */
const char* table_get(Table t, const char* key);

/**
 * @brief Retrieves the address associated with a key in the hash table.
 * @param t The hash table.
 * @param key The key string.
 * @return The address associated with the key, or -1 if not found.
 */
int table_get_address(Table t, const char* key);

#endif /** TABLE_H*/

