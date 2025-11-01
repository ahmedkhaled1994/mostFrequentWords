/*
 * Most Frequent Words - A C program to find most frequent words in text files
 * Copyright (c) 2025 ahmed khaled
 * Licensed under the MIT License - see LICENSE file for details
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#include "utility.h"
#include "mostFrequentWords.h"
#include "hashTable.h"

typedef struct 
{ 
    char *word; 
    int count; 
} WordCount;

static int cmpWordCount(const void *a, const void *b);

char **find_frequent_words(const char *path, int32_t n) {

    //create a file pointer
    FILE *fptr;
    char wordBuff[100];
    fptr = fopen(path, "r");
    if(fptr == NULL) {
        printf("Error opening file\n");
        return NULL;
    }

    //create a freq map 
    hashTable* freqMap = hashTable_create(NULL);
    if (freqMap == NULL) {
        printf("Error creating hash table\n");
        fclose(fptr);
        return NULL;
    }

    while(fscanf(fptr, "%99s", wordBuff)==1){
        //printf("%s,", wordBuff);
        clean_and_lowercase(wordBuff);
        hashTable_incrementOrInsert(freqMap, wordBuff);
        //printf("%s\n", wordBuff);
    }

    fclose(fptr);

    size_t length = hashTable_getLength(freqMap);
    WordCount *wordCountArray = (WordCount *)malloc(length * sizeof(WordCount));

    hashTable_iterator freqMapItr;
    hashTable_initIterator(freqMap, &freqMapItr);

    const char* key;
    void* value;
    size_t i = 0;
    while (hashTable_iteratorNext(&freqMapItr, &key, &value)) {
        int count = *(int*)value;
        printf("Word: %s, Count: %d\n", key, count);
        //populate word count array
        wordCountArray[i].word = strdup(key);
        wordCountArray[i].count = count;
        i++;
    }

    qsort(wordCountArray, length, sizeof(WordCount), cmpWordCount);

    char** result = (char**)malloc(n * sizeof(char*));
    for (int32_t i = 0; i < n && i < (int32_t)length; i++) {
        result[i] = strdup(wordCountArray[i].word);
        //printf("Top %d: %s (Count: %d)\n", i + 1, result[i], wordCountArray[i].count);
    }

    //TODO: create min heap 

    //delete freq map
    hashTable_destroy(freqMap);

    return result;
}


int main() {

    // find_frequent_words("test_simple.txt", 3);
    // find_frequent_words("test_punctuation.txt", 3);
    // find_frequent_words("test_ties.txt", 3);
    // find_frequent_words("test_large.txt", 3);
    char** freqWords = find_frequent_words("shakespeare.txt", 3);

    for (int i = 0; i < 3; i++) {
        printf("Frequent Word %d: %s\n", i + 1, freqWords[i]);
    }
    return 0;
}

static int cmpWordCount(const void *a, const void *b) {
    WordCount *wcA = (WordCount *)a;
    WordCount *wcB = (WordCount *)b;

    // Sort primarily by count in descending order
    if (wcA->count != wcB->count) {
        return wcB->count - wcA->count; // Descending order
    }
    // If counts are equal, sort alphabetically in ascending order
    return strcmp(wcA->word, wcB->word);
}
