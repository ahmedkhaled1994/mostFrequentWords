# Most Frequent Words

A C program that finds the most frequently occurring words in a text file.

## Project Structure
```
src/        - Source code files
include/    - Header files  
```

## Features
- Reads text files and processes words
- Cleans and normalizes words (removes punctuation, converts to lowercase)
- Finds the N most frequent words

## Building

### Using Make (Recommended)
```bash
make
```

### Manual Build (Alternative)
```bash
gcc -I include -Wall -Wextra -std=c99 -o mostFrequentWords src/mostFrequentWords.c
```

## Usage
```c
char **results = find_frequent_words("input.txt", 5);
```

## Running
```bash
./mostFrequentWords
```

## Clean Build Files
```bash
make clean
```

## License
MIT License - see LICENSE file for details.