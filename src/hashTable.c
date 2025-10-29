/*
 * hash table - hash table implementation in C
 * Copyright (c) 2025 ahmed khaled
 * Licensed under the MIT License - see LICENSE file for details
 */

#include <stddef.h>
#include <stdlib.h>
#include "hashTable_cfg.h"
#include "hashTable.h"

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
    ht->entries = calloc(ht->capacity, sizeof(ht_entry));
    
    // Check if entries allocation failed
    if (ht->entries == NULL)
    {
        free(ht);    // Clean up previously allocated hash table
        return NULL; // Return NULL on allocation failure
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
        // Free the key string 
        free((void*)ht->entries[i].key);
    }

    // Free the entries array that holds all the hash table slots
    free(ht->entries);
    // Finally, free the hash table structure itself
    free(ht);
}