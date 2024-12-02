#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Provides access to strtok function
#include <stdbool.h> // Provides access to bool type

/**
 * @brief Determines if an array of integers is safe or unsafe depending on 
 * whether or not the integers are always increasing or decreasing by at least 1 and at most 3.
 * 
 * @param array array of integers to check for safety.
 * @param count length of array.
 * @return true if the array is deemed as safe by satisfying the conditions described above.
 * @return false if the array is deemed as unsafe by not satisfying the conditions described above.
 */
bool isSafe(int *array, int count) {
    bool isIncreasing = true;
    bool isDecreasing = true;

    for (int i = 1; i < count; i++) {
        int diff = array[i] - array[i - 1];

        if (diff < -3 || diff > 3 || diff == 0) {
            return false;
        }

        if (diff > 0) {
            isDecreasing = false;
        } else if (diff < 0) {
            isIncreasing = false;
        }
    }
    return isIncreasing || isDecreasing;
}

/**
 * @brief Provides primary implementation and logic for reading from a file and displaying the total safe and unsafe entry counts.
 * 
 * @return int 0 for successful program execution.
 */
int main(void) {
    FILE *file = fopen("input.txt", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int array[20];
    int count, safeCount = 0, unsafeCount = 0;

    while ((read = getline(&line, &len, file)) != -1) {
        char *token = strtok(line, " ");
        count = 0;

        while (token != NULL) {
            array[count++] = atoi(token);
            token = strtok(NULL, " ");
        }

        if (isSafe(array, count)) {
            safeCount++;
        } else {
            bool dampenedSafe = false;
            for (int i = 0; i < count; i++) {
                int tempArray[20];
                int tempCount = 0;

                for (int j = 0; j < count; j++) {
                    if (j != i) {
                        tempArray[tempCount++] = array[j];
                    }
                }

                if (isSafe(tempArray, tempCount)) {
                    dampenedSafe = true;
                    break;
                }
            }

            if (dampenedSafe) {
                safeCount++;
            } else {
                unsafeCount++;
            }
        }
    }

    fclose(file);
    if (line) {
        free(line);
    }
    printf("SafeCount: %d\n", safeCount);
    printf("UnsafeCount: %d\n", unsafeCount);

    return EXIT_SUCCESS;
}