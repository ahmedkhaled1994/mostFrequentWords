/*
 * hash table - hash table implementation in C
 * Copyright (c) 2025 ahmed khaled
 * Licensed under the MIT License - see LICENSE file for details
 */

#include <stddef.h>
#include <stdlib.h>
#include "hashTable_cfg.h"
#include "hashTable.h"

/*========================================================== */
/*============== Private Function Declarations ============= */
/*========================================================== */

/**
 * @brief DJB2 hash function for string keys
 * 
 * This is a simple hash function from Daniel J. Bernstein. It uses the magic
 * number 5381 (which is a prime) and multiplies by 33 (shifting left by 5 and
 * adding) for each character in the string.
 * 
 * @param str The null-terminated string to hash
 * 
 * @return The hash value as an unsigned long
 * 
 * @note This is a private function, only accessible within this file
 * @note The function assumes str is not NULL (caller responsibility)
 * 
 * @algorithm
 *   hash = 5381
 *   for each character c in str:
 *     hash = hash * 33 + c
 * 
 * @example
 *   unsigned long hash = hash_djb2("hello");
 */
static unsigned long hash_djb2(const char *str);

/*========================================================== */
/*==================== Public Functions ==================== */
/*========================================================== */
hashTable* hashTable_create(hashTable_config* config) {
    
    size_t tableCapacity;
    double tableMaxLoadFactor;

    // Check if custom configuration is provided
    if (config == NULL)
    {
        // Use default configuration values when no config is provided
        tableCapacity = (size_t)HASHTABLE_DEFAULT_CAPACITY;
        tableMaxLoadFactor = (double)HASHTABLE_DEFAULT_MAX_LOAD_FACTOR;
    }
    else 
    {
        // Use provided configuration values
        tableCapacity = config->initial_capacity;
        tableMaxLoadFactor = config->max_load_factor;
    }

    // Allocate memory for the hash table structure
    hashTable *ht = malloc(sizeof(hashTable));

    // Check if memory allocation failed
    if (ht == NULL)
    {   
        return NULL; // Return NULL on allocation failure
    }
    
    // Initialize hash table properties
    ht->capacity = tableCapacity;               // Set table capacity
    ht->max_load_factor = tableMaxLoadFactor;   // Set maximum load factor
    ht->length = 0;                             // Initialize current size to 0
    
    // Allocate and zero-initialize the entries array
    ht->entries = (ht_entry**)calloc(ht->capacity, sizeof(ht_entry*));
    
    // Check if entries allocation failed
    if (ht->entries == NULL)
    {
        free(ht);    // Clean up previously allocated hash table
        return NULL; // Return NULL on allocation failure
    }
    // Initialize each entry in the entries array
    for (size_t i = 0; i < ht->capacity; i++) {
        ht->entries[i] = NULL; // Set each slot to NULL (empty)
    }

    return ht; // Return successfully created hash table
}

void hashTable_destroy(hashTable* ht)
{
    // Check if hash table pointer is valid (defensive programming)
    if (ht == NULL) {
        return; // Nothing to destroy if pointer is NULL
    }
    
    // Iterate through all slots in the hash table
    for (size_t i = 0; i < ht->capacity; i++) {
        ht_entry* entry = ht->entries[i];
        // TODO: revise after linked list implementation for collision resolution
        if (entry != NULL) {
            // Free the key string if dynamically allocated
            free((void*)entry->key);
            // Free the value pointer if dynamically allocated
            free(entry->value);
            // Free the entry structure itself
            free(entry);
        }
    }

    // Free the entries array that holds all the hash table slots
    free(ht->entries);
    // Finally, free the hash table structure itself
    free(ht);
}

void* hashTable_lookup(hashTable* ht, const char* key) {
    // TODO: add other hashing algorithms support
    // Compute the hash value for the given key
    unsigned long hashValue = hash_djb2(key);
    size_t index = hashValue % ht->capacity;

    //declare current entry pointer
    ht_entry *currentEntry = ht->entries[index];

    // Traverse the linked list at this index to find the key
    while (currentEntry != NULL)
    {
        if (strcmp(key, currentEntry->key) == 0) 
        {
            return currentEntry->value;
        }
        // Move to the next entry in the linked list
        currentEntry = currentEntry->next;
    }

    return NULL; // Key not found
}
/*========================================================== */
/*==================== Private Functions =================== */
/*========================================================== */
static unsigned long hash_djb2(const char *str) {
    unsigned long hash = 5381; // Initial hash value, a prime number
    int c; // To store each character of the string

    // Loop through the string until the null terminator is reached
    while ((c = *str++)) 
    {
        // Core hashing operation: hash * 33 + c
        hash = ((hash << 5) + hash) + c; 
    }

    return hash;
}

//TODO: implement hash table resize
// TODO: implement collision resolution (e.g., linear probing, chaining)
// TODO: implement rehashing when load factor exceeds max_load_factor
// TODO: implement hash table insert 
// TODO: implement hash table delete
// TODO: implement public getters for length and capacity
// TODO: revise all public API functions for error handling and edge cases