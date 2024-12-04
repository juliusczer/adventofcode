#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/** Arbitrary line size. */
#define MAX_SIZE 1000

int directions[8][2] = {
    {0, 1},   // Right
    {1, 0},   // Down
    {0, -1},  // Left
    {-1, 0},  // Up
    {1, 1},   // Down-right diagonal
    {1, -1},  // Down-left diagonal
    {-1, 1},  // Up-right diagonal
    {-1, -1}  // Up-left diagonal
};

/**
 * @brief PART 1: Searches for a word in a 2d array of chars and returns true if the word exists, false otherwise.
 * 
 * @param grid 2d char array to search through
 * @param rows number of rows in grid
 * @param cols number of columns in grid
 * @param row row index
 * @param col column index
 * @param word word to search for
 * @param dir direction index
 * @return true if the word exists within the array.
 * @return false if the word does not exist within the array.
 */
bool searchWord(char grid[MAX_SIZE][MAX_SIZE], int rows, int cols, int row, int col, char *word, int dir[2]) {
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int newRow = row + i * dir[0];
        int newCol = col + i * dir[1];
        if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols || grid[newRow][newCol] != word[i]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief PART 1: Aggregates the number of times the word appears in the 2d array.
 * 
 * @param grid 2d array to search through
 * @param rows number of rows in grid
 * @param cols number of columns in grid
 * @param word word to search for and aggregate occurances
 * @return int number of occurances of the given word in the grid.
 */
int countOccurrences(char grid[MAX_SIZE][MAX_SIZE], int rows, int cols, char *word) {
    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < 8; k++) {
                if (searchWord(grid, rows, cols, i, j, word, directions[k])) {
                    count++;
                }
            }
        }
    }
    return count;
}

/**
 * @brief PART 2: Searches for "MAS" occuring in an "X" shape in the given location in the given grid.
 * 
 * @param grid 2d char array to search through
 * @param rows number of rows in grid
 * @param cols number of columns in grid
 * @param row row index
 * @param col column index 
 * @param rowOffset row offset index
 * @param colOffset column offset index
 * @return true if "MAS" or "SAM" is found at the given location.
 * @return false if "MAS" or "SAM" is not found at the given location.
 */
bool isMAS(char grid[MAX_SIZE][MAX_SIZE], int rows, int cols, int row, int col, int rowOffset, int colOffset) {
    // Check bounds for the three characters
    for (int i = 0; i < 3; i++) {
        int newRow = row + i * rowOffset;
        int newCol = col + i * colOffset;
        if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols) {
            return false; // Out of bounds
        }
    }
    // Check for "MAS" or "SAM"
    if ((grid[row][col] == 'M' && grid[row + rowOffset][col + colOffset] == 'A' && grid[row + 2 * rowOffset][col + 2 * colOffset] == 'S') ||
        (grid[row][col] == 'S' && grid[row + rowOffset][col + colOffset] == 'A' && grid[row + 2 * rowOffset][col + 2 * colOffset] == 'M')) {
        return true;
    }
    return false;
}

/**
 * @brief PART 2: Aggregates the number of occurances of "MAS" occuring in an "X" shape in the given grid.
 * 
 * @param grid 2d char array to search through
 * @param rows number of rows in grid
 * @param cols number of columns in grid
 * @return int number of occurances of the "MAS" pattern in the grid.
 */
int countXMAS(char grid[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    int count = 0;

    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            if (grid[i][j] == 'A') { // Check if the cell is a valid center
                if (isMAS(grid, rows, cols, i - 1, j - 1, 1, 1) && isMAS(grid, rows, cols, i - 1, j + 1, 1, -1)) {
                    count++;
                }
            }
        }
    }
    return count;
}

/**
 * @brief Contains logic for reading an input file and aggregating the number of "XMAS" and "X-MAS" occurances in the input file. 
 * 
 * @return int 0 for successful program execution.
 */
int main() {
    FILE *file = fopen("input.txt", "r");

    char grid[MAX_SIZE][MAX_SIZE];
    int rows = 0;
    int cols = 0;
    char line[MAX_SIZE];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        if (cols == 0) {
            cols = strlen(line);
        }
        strcpy(grid[rows], line);
        rows++;
    }
    fclose(file);

    int resultP1 = countOccurrences(grid, rows, cols, "XMAS");

    int resultP2 = countXMAS(grid, rows, cols);

    printf("Total (Part 1): %d\n", resultP1);
    printf("Total (Part 2): %d\n", resultP2);

    return EXIT_SUCCESS;
}