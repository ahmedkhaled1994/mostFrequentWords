/*
 * Most Frequent Words - A C program to find most frequent words in text files
 * Copyright (c) 2025 ahmed khaled
 * Licensed under the MIT License - see LICENSE file for details
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void clean_and_lowercase(char *word) {
    char *srcPtr = word;
    char *dstPtr = word;
    while(*srcPtr) {
        // Check if the character is NOT punctuation
        if (!ispunct(*srcPtr)) {
            *dstPtr = tolower(*srcPtr);
            dstPtr++; // Move destination pointer forward
        }
        srcPtr++; // Move source pointer forward
    }
    *dstPtr = '\0'; // Null-terminate the cleaned string
}
char **find_frequent_words(const char *path, int32_t n) {
    //create a file pointer
    FILE *fptr;
    char lineBuff[100];
    char wordBuff[100];
    fptr = fopen(path, "r");
    if(fptr == NULL) {
        printf("Error opening file\n");
        return NULL;
    }

    while(fscanf(fptr, "%99s", wordBuff)==1){
        printf("%s,", wordBuff);
        clean_and_lowercase(wordBuff);
        printf("%s\n", wordBuff);
    }

    fclose(fptr);
    return NULL;
}


int main() {

    find_frequent_words("shakespeare.txt", 5);
    return 0;
}
