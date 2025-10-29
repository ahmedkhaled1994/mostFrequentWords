/*
 * hash table - hash table implementation in C
 * Copyright (c) 2025 ahmed khaled
 * Licensed under the MIT License - see LICENSE file for details
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

// Hash table entry structure - represents a key-value pair
typedef struct {
    const char* key;  // key is NULL if this slot is empty
    void* value;      // pointer to the value data
} ht_entry;

// Main hash table structure
typedef struct hashTable {
    ht_entry* entries;          // hash slots array
    double max_load_factor;     // maximum load factor before resizing
    size_t capacity;            // size of entries array
    size_t length;              // number of items currently in hash table
} hashTable;

// Configuration structure for hash table creation
typedef struct {
    size_t initial_capacity;    // initial number of slots to allocate
    double max_load_factor;     // load factor threshold for resizing
} hashTable_config;

/**
 * Creates a new hash table with the specified configuration
 * 
 * @param config Pointer to configuration struct containing initial_capacity 
 *               and max_load_factor. Pass NULL to use default values.
 * 
 * @return Pointer to newly created hash table on success, NULL on failure
 * 
 * @note The caller is responsible for freeing the returned hash table
 *       using hashTable_destroy() when no longer needed.
 * 
 * @example
 *   // Create with default settings
 *   hashTable* ht = hashTable_create(NULL);
 * 
 *   // Create with custom settings
 *   hashTable_config config = {32, 0.8};
 *   hashTable* ht = hashTable_create(&config);
 */
hashTable* hashTable_create(hashTable_config* config);

/**
 * Destroys a hash table and frees all associated memory
 * 
 * @param ht Pointer to the hash table to destroy. Can be NULL (no-op).
 * 
 * @note This function will:
 *       - Free all key-value pairs stored in the hash table
 *       - Free the entries array
 *       - Free the hash table structure itself
 *       - Set the pointer to NULL is recommended after calling this function
 * 
 * @warning Do not use the hash table pointer after calling this function
 * 
 * @example
 *   hashTable* ht = hashTable_create(NULL);
 *   // ... use hash table ...
 *   hashTable_destroy(ht);
 *   ht = NULL; // Good practice
 */
void hashTable_destroy(hashTable* ht);

#endif /* HASHTABLE_H */