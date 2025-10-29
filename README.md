# Most Frequent Words

A C program that finds the most frequently occurring words in a text file.

## Features
- Reads text files and processes words
- Cleans and normalizes words (removes punctuation, converts to lowercase)
- Finds the N most frequent words

## Usage
```c
char **results = find_frequent_words("input.txt", 5);
```

## Building
```bash
gcc -o mostFrequentWords mostFrequentWords.c
```

## License
MIT License - see LICENSE file for details.