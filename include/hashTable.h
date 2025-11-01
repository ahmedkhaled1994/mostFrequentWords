/*
 * hash table - hash table implementation in C
 * Copyright (c) 2025 ahmed khaled
 * Licensed under the MIT License - see LICENSE file for details
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

// Hash table entry structure - represents a key-value pair
typedef struct ht_entry{
    const char* key;  // key is NULL if this slot is empty
    void* value;      // pointer to the value data
    struct ht_entry* next;   // pointer to the next entry in case of collision (for chaining)
} ht_entry;

// Main hash table structure
typedef struct hashTable {
    ht_entry** entries;          // hash slots array
    double max_load_factor;     // maximum load factor before resizing
    size_t capacity;            // size of entries array
    size_t length;              // number of items currently in hash table
} hashTable;

// Configuration structure for hash table creation
typedef struct {
    size_t initial_capacity;    // initial number of slots to allocate
    double max_load_factor;     // load factor threshold for resizing
} hashTable_config;

//iterator struct 
typedef struct {
    hashTable* ht;              // pointer to the hash table being iterated
    size_t current_index;       // current index in the entries array
    ht_entry* current_entry;    // current entry in the linked list at current index
} hashTable_iterator;

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

/**
 * Looks up a value by key in the hash table
 * 
 * @param ht Pointer to the hash table
 * @param key The key string to look up
 * 
 * @return Pointer to the value associated with the key, or NULL if not found
 * 
 * @note The caller should not modify or free the returned value pointer
 * 
 * @example
 *   hashTable* ht = hashTable_create(NULL);
 *   // ... insert some key-value pairs ...
 *   void* value = hashTable_lookup(ht, "exampleKey");
 *   if (value != NULL) {
 *       // Key found, use value
 *   } else {
 *       // Key not found
 *   }
 */
void* hashTable_lookup(hashTable* ht, const char* key);

/**
 * Inserts or updates a key-value pair in the hash table
 * 
 * @param ht Pointer to the hash table
 * @param key The key string to insert or update
 * @param value Pointer to the value data to associate with the key
 * 
 * @return Pointer to the inserted/updated value on success, NULL on failure
 * 
 * @note If the key already exists, its value will be updated to the new value
 *       If the key does not exist, a new entry will be created
 * 
 * @example
 *   hashTable* ht = hashTable_create(NULL);
 *   int data = 42;
 *   void* result = hashTable_insert(ht, "exampleKey", &data);
 *   if (result != NULL) {
 *       // Insert/update successful
 *   } else {
 *       // Insert/update failed
 *   }
 */
void* hashTable_insert(hashTable* ht, const char* key, const void* value);

/**
 * Increments an integer value associated with the given key in the hash table
 * 
 * @param ht Pointer to the hash table
 * @param key The key string whose associated integer value to increment
 * 
 * @return Pointer to the incremented integer value on success, NULL on failure
 * 
 * @note If the key does not exist, a new entry will be created with initial value 1
 *       The value associated with the key must be of type int*
 * 
 * @example
 *   hashTable* ht = hashTable_create(NULL);
 *   int* value = (int*)hashTable_incrementOrInsert(ht, "counterKey");
 *   if (value != NULL) {
 *       // Successfully incremented, use *value
 *   } else {
 *       // Increment failed
 *   }
 */
void* hashTable_incrementOrInsert(hashTable* ht, const char* key);

void* hashTable_updateOrInsert(hashTable* ht, const char* key, 
                               void* defaultValue, 
                               void* (*updateFunc)(void* existingValue));

/**
 * @brief Initializes a hash table iterator to traverse all key-value pairs
 * 
 * This function prepares an iterator for traversing all entries in the hash table.
 * After initialization, the iterator is positioned at the first valid entry if one exists.
 * 
 * @param ht Pointer to the hash table to iterate over. Must not be NULL.
 * @param iter Pointer to the iterator structure to initialize. Must not be NULL.
 * 
 * @note After calling this function, use hashTable_iteratorNext() to retrieve entries
 * @note If the hash table is empty, the iterator will be in a valid but finished state
 * @note The iterator becomes invalid if the hash table is modified during iteration
 * 
 * @warning The hash table must remain valid for the entire duration of iteration
 * @warning Do not modify the hash table while iterating (undefined behavior)
 * 
 * @example
 *   hashTable* ht = hashTable_create(NULL);
 *   // ... insert some entries ...
 *   
 *   hashTable_iterator iter;
 *   hashTable_initIterator(ht, &iter);
 *   
 *   const char* key;
 *   void* value;
 *   while (hashTable_iteratorNext(&iter, &key, &value)) {
 *       printf("Key: %s\n", key);
 *   }
 */
void hashTable_initIterator(hashTable* ht, hashTable_iterator* iter);

/**
 * @brief Retrieves the next key-value pair from the hash table iterator
 * 
 * This function advances the iterator to the next entry and returns the key-value pair.
 * The iteration order is not guaranteed and depends on the internal hash table structure.
 * 
 * @param iter Pointer to the iterator structure. Must not be NULL.
 * @param key Pointer to store the key string pointer. Must not be NULL.
 * @param value Pointer to store the value pointer. Must not be NULL.
 * 
 * @return true if a valid entry was retrieved, false if no more entries exist
 * 
 * @note The returned key and value pointers are valid until the hash table is modified
 * @note Do not free or modify the returned key pointer
 * @note The value pointer points to the actual stored data
 * @note Call this function repeatedly until it returns false to traverse all entries
 * 
 * @warning The iterator becomes invalid if the hash table is modified during iteration
 * @warning The returned pointers become invalid if the hash table is destroyed or modified
 * 
 * @example
 *   hashTable_iterator iter;
 *   hashTable_initIterator(freqMap, &iter);
 *   
 *   const char* word;
 *   void* countPtr;
 *   while (hashTable_iteratorNext(&iter, &word, &countPtr)) {
 *       int count = *(int*)countPtr;
 *       printf("Word: '%s', Count: %d\n", word, count);
 *   }
 */
bool hashTable_iteratorNext(hashTable_iterator* iter, const char** key, void** value);

#endif /* HASHTABLE_H */


// TODO: create hashtable iterator struct 
// TODO: add functions to initialize and get next key-value pair
// TODO: review struct documentation following doxygen 
