#include <iostream>
#include <fstream>
#include <algorithm> // Provides sorting algroithm for arrays.
#include <unordered_map> // Provides map implementation for accumulating frequencies in computeSimilarityScore.

/**
 * @brief Returns the number of lines in the given file.
 * 
 * @param fileName name of file to return number of lines.
 * @return int number of lines in file.
 */
int getLines(std::string fileName) {
    std::ifstream file(fileName);
    std::string str;
    int lineNum = 0;
    while (std::getline(file, str)) {
        lineNum++;
    }
    return lineNum;
}

/**
 * @brief Computes the distance value for each array element and returns 
 * the accumulated sum of differences for each pair of elements.
 * 
 * @param length length of arrays.
 * @param arr1 first array (left).
 * @param arr2 second array (right).
 * @return int the accumulated distance (difference) between all element pairs in the arrays.
 */
int computeDistance(int length, int *arr1, int *arr2) {
    int instancedDistance = 0;
    int totalDistance = 0;
    for (int i = 0 ; i < length; i++) {
        if (arr1[i] > arr2[i]) {
            instancedDistance = arr1[i] - arr2[i];
        } else {
            instancedDistance = arr2[i] - arr1[i];
        }
        totalDistance += instancedDistance;
    }

    return totalDistance;
}

/**
 * @brief Computes the similarity score (the product of a given element in the first array 
 * and the number of instances of that element in the second array) 
 * 
 * @param length length of arrays.
 * @param arr1 first array (left).
 * @param arr2 second array (right).
 * @return unsigned long long the accumulated total similarity score of all element pairs in the arrays.
 */
int computeSimilarityScore(int length, int *arr1, int *arr2) {
    int total = 0;

    std::unordered_map<int, int> freqMap;
    for (int i = 0; i < length; i++) {
        freqMap[arr2[i]]++;
    }

    for (int i = 0; i < length; i++) {
        int count = freqMap[arr1[i]];
        total += arr1[i] * count;
    }
    return total;
}

/**
 * @brief Reads in integer values from a given file name and stores them in arrays that are 
 * sorted in ascending order and used for distance and similarity computations.
 * 
 * @param fileName name of file to parse.
 */
void parseFile(std::string fileName) {
    std::ifstream file(fileName);
    std::string test; 
    int length = getLines(fileName);
    int left[length];
    int right[length];
    int leftInt = 0;
    int rightInt = 0;
    int counter = 0;

    while (std::getline(file, test)) {
        sscanf(test.c_str(), "%d %d", &leftInt, &rightInt);
        left[counter] = leftInt;
        right[counter] = rightInt;
        counter++;
    }

    std::sort(left, left + length);
    std::sort(right, right + length);
    std::cout << "Total Distance: " << computeDistance(length, left, right) << "\n";
    std::cout << "Total Similarity Score: " << computeSimilarityScore(length, left, right) << "\n";
}

/**
 * @brief parses input file from Advent Of Code Day 1 2024.
 * 
 * @return int zero for successful program execution.
 */
int main() {
    parseFile("test.txt");
    return 0;
}