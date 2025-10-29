/*
 * Most Frequent Words - Word processing utilities
 * Copyright (c) 2025 ahmed khaled
 * Licensed under the MIT License - see LICENSE file for details
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "utility.h"

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