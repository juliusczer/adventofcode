/**
 * The following implementation only contains a working solution for part 1 of Day 6, 2024 Advent of Code.
 */
#include <stdio.h>
#include <string.h>

/* Arbitrary constants for matrix. */
#define MAX_ROWS 1000
#define MAX_COLS 1000

// Directions: 0 = Up, 1 = Right, 2 = Down, 3 = Left
const int directionX[] = {-1, 0, 1, 0};
const int directionY[] = {0, 1, 0, -1};

/**
 * @brief Helper function for printing out the matrix, largely used for debugging.
 * 
 * @param map matrix to print out
 * @param rows number of rows in matrix
 * @param cols number of columns in matrix
 */
void printMap(char map[MAX_ROWS][MAX_COLS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        printf("%s\n", map[i]);
    }
    printf("\n");
}

/**
 * @brief Contains logic for reading from an input file and traversing 
 * through the path of the matrix with directional turning and bounds checking.
 * 
 * @return int 0 for successful program execution.
 */
int main() {
    char map[MAX_ROWS][MAX_COLS];
    int rows = 0, cols = 0;

    FILE *file = fopen("input.txt", "r");

    // Read the input map from the file
    while (fgets(map[rows], MAX_COLS, file)) {
        map[rows][strcspn(map[rows], "\n")] = '\0';
        rows++;
    }
    cols = strlen(map[0]);
    fclose(file);

    // Find the guard's starting position and direction
    int x = -1, y = -1, direction = -1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == '^') {  // Up
                x = i; 
                y = j; 
                direction = 0; 
            } else if (map[i][j] == '>') { // Right
                x = i; 
                y = j; 
                direction = 1;
            } else if (map[i][j] == 'v') { // Down
                x = i; 
                y = j; 
                direction = 2; 
            } else if (map[i][j] == '<') { // Left
                x = i; 
                y = j; 
                direction = 3; 
            }
        }
    }

    int xCount = 0;
    // Simulate route
    while (1) {
        if (map[x][y] == '.' || map[x][y] == '<' || map[x][y] == '^' || map[x][y] == '>' || map[x][y] == 'v') {
            map[x][y] = 'X';
            xCount++;
        }

        int newDirectionX = x + directionX[direction];
        int newDirectionY = y + directionY[direction];

        // Break if the position moves out of bounds
        if (newDirectionX < 0 || newDirectionX >= rows || newDirectionY < 0 || newDirectionY >= cols) {
            break;
        }

        // Check the next position
        if (map[newDirectionX][newDirectionY] == '#') {
            // Turn right if '#' in next position
            direction = (direction + 1) % 4;
        } else {
            // Move forward if the next position is valid
            x = newDirectionX;
            y = newDirectionY;
        }
    }

    // Print the resulting map
    printMap(map, rows, cols);
    printf("Number of X's [Part 1]: %d\n", xCount);

    return 0;
}