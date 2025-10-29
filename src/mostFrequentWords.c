/*
 * Most Frequent Words - A C program to find most frequent words in text files
 * Copyright (c) 2025 ahmed khaled
 * Licensed under the MIT License - see LICENSE file for details
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "utility.h"
#include "mostFrequentWords.h"
#include "hashTable.h"


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
        printf("%s,", wordBuff);
        clean_and_lowercase(wordBuff);
        // TODO: add wordBuff to hash map
        printf("%s\n", wordBuff);
    }

    fclose(fptr);

    //TODO: create min heap 

    //delete freq map
    hashTable_destroy(freqMap);

    return NULL;
}


int main() {

    find_frequent_words("shakespeare.txt", 5);
    return 0;
}
