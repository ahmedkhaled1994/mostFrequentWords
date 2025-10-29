/*
 * Most Frequent Words - Main header
 * Copyright (c) 2025 ahmed khaled
 * Licensed under the MIT License - see LICENSE file for details
 */

#ifndef MOST_FREQUENT_WORDS_H
#define MOST_FREQUENT_WORDS_H

#include <stdint.h>

/**
 * Find the N most frequent words in a text file
 * @param path Path to the text file
 * @param n Number of top words to return
 * @return Array of strings containing the most frequent words
 */
char **find_frequent_words(const char *path, int32_t n);

#endif // MOST_FREQUENT_WORDS_H