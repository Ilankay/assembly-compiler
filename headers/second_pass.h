#ifndef SECOND_PASS_H
#define SECOND_PASS_H

/**
 * @file second_pass.h
 * @brief Second pass for processing assembly code.
 *
 * This module performs the second pass of processing the assembly file, dealing with the 
 * instructions and handling entries and external symbols. It updates the instruction 
 * list and manages the external and entry symbol lists.
 *
 * Author: [Your Name]
 * Date: [Date]
 */

/** Structs*/

/**
 * @brief Structure containing results of the second pass.
 */
typedef struct SecondPassPack {
    Node* instruction_list;  /**< Linked list of instructions after second pass processing */
    Node* external_list;     /**< Linked list of external symbols */
    Node* data_list;         /**< Linked list of data from the first pass */
    Node* entry_list;        /**< Linked list of entry symbols */
    int ICF;                 /**< Instruction Count Final */
    int DCF;                 /**< Data Count Final */
} SecondPassPack;

/** Functions*/

/**
 * @brief Performs the second pass of the assembly code.
 * @param fpp The result from the first pass, including symbol table, instruction list, etc.
 * @param filename The name of the assembly file to process.
 * @return A SecondPassPack structure containing the updated lists and counts.
 */
SecondPassPack second_pass(FirstPassPack fpp, char* filename);

#endif /** SECOND_PASS_H*/
