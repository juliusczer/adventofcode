#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool enablePart2 = true; // Flag to enable/disable conditional checks for do and don't keywords required for part 2.
bool mulEnabled = true;

/**
 * @brief Parses a given line of input by searching for do, don't, and mul keywords and executing operations accordingly.
 * 
 * @param line line of input to parse.
 * @return int the total of each multiplication performed within the given line.
 */
int parseAndSumMul(const char *line) {
    int total = 0;
    const char *ptr = line;

    while (*ptr) {
        
        if (enablePart2 && strncmp(ptr, "don't()", 7) == 0) {
            mulEnabled = false;
            ptr += 7;
        } else if (enablePart2 && strncmp(ptr, "do()", 4) == 0) {
            mulEnabled = true;
            ptr += 4;
        } else if (strncmp(ptr, "mul(", 4) == 0) {
            if (mulEnabled) {
                ptr += 4;
                int num1 = 0, num2 = 0;

                // Parse the first number
                while (isdigit(*ptr)) {
                    num1 = num1 * 10 + (*ptr - '0');
                    ptr++;
                }

                if (*ptr == ',') {
                    ptr++;
                } else {
                    continue;
                }

                // Parse the second number
                while (isdigit(*ptr)) {
                    num2 = num2 * 10 + (*ptr - '0');
                    ptr++;
                }

                if (*ptr == ')') {
                    total += num1 * num2;
                    ptr++;
                } else {
                    continue;
                }
            } else {
                ptr = strstr(ptr, ")");
                if (ptr) {
                    ptr++;
                }
            }
        } else {
            ptr++;
        }
    }

    return total;
}

/**
 * @brief Contains logic for reading an input file aggregating the total for each line of input obtained by parseAndSumMul.
 * 
 * @return int 0 for successful program execution.
 */
int main() {
    FILE *file = fopen("input.txt", "r");

    char *line = NULL;
    size_t len = 0;
    int total = 0;

    while ((getline(&line, &len, file)) != -1) {
        total += parseAndSumMul(line);
    }

    free(line);
    fclose(file);

    printf("Total: %d\n", total);

    return EXIT_SUCCESS;
}