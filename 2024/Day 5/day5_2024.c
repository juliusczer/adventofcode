#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/** Constant for the number of rules possible. */
#define MAX_RULES 10000

/**
 * @brief Struct representation for each rule containing an integer before and after it.
 */
typedef struct {
    int before;
    int after;
} Rule;

/**
 * @brief PART 1: Checks if a given update satisfies the currently defined set of rules.
 * 
 * @param update pointer to update sequence to determine proper ordering
 * @param update_size length of given update sequence
 * @param rules set of all defined ordering rules
 * @param rule_count number of rule structs in rules
 * @return true if the update sequence satisfies the set of defined ordering rules.
 * @return false if the update sequence does not satisfy the set of defined ordering rules.
 */
bool isOrdered(int *update, int update_size, Rule *rules, int rule_count) {
    for (int i = 0; i < rule_count; i++) {
        int before_index = -1, after_index = -1;
        for (int j = 0; j < update_size; j++) {
            if (update[j] == rules[i].before) {
                before_index = j;
            }
            if (update[j] == rules[i].after) {
                after_index = j;
            }
        }

        if (before_index != -1 && after_index != -1 && before_index > after_index) {
            return false;
        }
    }
    return true;
}

/**
 * @brief PART 2: Reorders the given update sequence into the correct order based on ordering rules.
 * 
 * @param update update sequence to reorder
 * @param update_size length of update sequence
 * @param rules ordering rules
 * @param rule_count number of defined ordering rules
 */
void reorderUpdate(int *update, int update_size, Rule *rules, int rule_count) {
    for (int i = 0; i < update_size - 1; i++) {
        for (int j = i + 1; j < update_size; j++) {
            for (int k = 0; k < rule_count; k++) {
                if (update[i] == rules[k].after && update[j] == rules[k].before) {
                    int temp = update[i];
                    update[i] = update[j];
                    update[j] = temp;
                }
            }
        }
    }
}

/**
 * @brief Provides logic for reading file input and processing updates with above functions.
 * 
 * @return int 0 for successful program execution.
 */
int main() {

    FILE *file = fopen("input.txt", "r");

    Rule rules[MAX_RULES];
    int rule_count = 0;
    int **updates = NULL;
    int *update_sizes = NULL;
    int update_count = 0;

    char line[256];

    // Read rules
    while (fgets(line, sizeof(line), file)) {
        if (strchr(line, '|')) {
            sscanf(line, "%d|%d", &rules[rule_count].before, &rules[rule_count].after);
            rule_count++;
        } else {
            break;
        }
    }

    // Allocate memory for updates
    updates = malloc(MAX_RULES * sizeof(int *));
    update_sizes = malloc(MAX_RULES * sizeof(int));

    // Read updates
    do {
        int size = 0;
        int *current_update = malloc(100 * sizeof(int));

        char *token = strtok(line, ",\n");
        while (token) {
            current_update[size++] = atoi(token);
            token = strtok(NULL, ",\n");
        }
        updates[update_count] = current_update;
        update_sizes[update_count++] = size;
    } while (fgets(line, sizeof(line), file));

    fclose(file);

    int sum_of_middle_pages = 0;
    int sum_of_reordered_middle_pages = 0;

    // Aggregate sums of middle pages in updates.
    for (int i = 0; i < update_count; i++) {
        if (isOrdered(updates[i], update_sizes[i], rules, rule_count)) { // Proper order
            int middle = updates[i][update_sizes[i] / 2];
            sum_of_middle_pages += middle;
        } else {                                                         // Improper order
            reorderUpdate(updates[i], update_sizes[i], rules, rule_count);
            int middle = updates[i][update_sizes[i] / 2];
            sum_of_reordered_middle_pages += middle;
        }
        free(updates[i]);
    }

    free(updates);
    free(update_sizes);

    printf("Sum of middle pages (Part 1): %d\n", sum_of_middle_pages);
    printf("Sum of unordered middle pages (Part 2): %d\n", sum_of_reordered_middle_pages);

    return 0;
}
