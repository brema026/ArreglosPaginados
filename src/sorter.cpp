#include "sorter.h"
#include "PagedArray.h"
#include "quicksort.h"
#include "insertionSort.h"
#include "bubbleSort.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <cstring>

// Function to print usage instructions
void printUsage() {
    std::cerr << "Usage: sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITHM>" << std::endl;
    std::cerr << "Algorithms: QS (Quick Sort), IS (Insertion Sort), BS (Bubble Sort)" << std::endl;
}

// Function to copy the input binary file to a temporary file
bool copyFile(const std::string& inputFilePath, const std::string& tempFilePath) {
    std::ifstream src(inputFilePath, std::ios::binary);
    std::ofstream dest(tempFilePath, std::ios::binary);
    if (!src || !dest) {
        std::cerr << "Error opening file for copying: " << inputFilePath << std::endl;
        return false;
    }
    dest << src.rdbuf();
    src.close();
    dest.close();
    return true;
}

void sortFile(const std::string& inputFilePath, const std::string& outputFilePath, const std::string& algorithm) {
    std::string tempBinaryFilePath = "temp_file.bin";

    // Copy input file to temporary file
    if (!copyFile(inputFilePath, tempBinaryFilePath)) {
        return;
    }

    // Open the temporary binary file for sorting
    std::ifstream inFile(tempBinaryFilePath, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening file for reading: " << tempBinaryFilePath << std::endl;
        return;
    }

    // Initialize PagedArray
    PagedArray pagedArray(inFile);

    // Load all integers from file into vector
    std::vector<int> numbers;
    for (size_t i = 0; i < pagedArray.size(); ++i) {
        numbers.push_back(pagedArray[i]);
    }

    // Sort the numbers
    auto start = std::chrono::high_resolution_clock::now();
    if (algorithm == "QS") {
        quicksort(numbers, 0, numbers.size() - 1);
    } else if (algorithm == "IS") {
        insertionSort(numbers);
    } else if (algorithm == "BS") {
        bubbleSort(numbers);
    } else {
        std::cerr << "Unknown sorting algorithm: " << algorithm << std::endl;
        printUsage();
        return;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Write sorted numbers to output CSV file
    std::ofstream outFileCSV(outputFilePath);
    if (!outFileCSV) {
        std::cerr << "Error opening file for writing: " << outputFilePath << std::endl;
        return;
    }

    for (size_t i = 0; i < numbers.size(); ++i) {
        outFileCSV << numbers[i];
        if (i != numbers.size() - 1) {
            outFileCSV << ",";
        }
    }
    outFileCSV.close();

    std::cout << "File sorted and saved to: " << outputFilePath << std::endl;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        printUsage();
        return 1;
    }

    std::string inputFilePath;
    std::string outputFilePath;
    std::string algorithm;

    for (int i = 1; i < argc; i += 2) {
        if (std::strcmp(argv[i], "-input") == 0) {
            inputFilePath = argv[i + 1];
        } else if (std::strcmp(argv[i], "-output") == 0) {
            outputFilePath = argv[i + 1];
        } else if (std::strcmp(argv[i], "-alg") == 0) {
            algorithm = argv[i + 1];
        } else {
            printUsage();
            return 1;
        }
    }

    if (inputFilePath.empty() || outputFilePath.empty() || algorithm.empty()) {
        printUsage();
        return 1;
    }

    sortFile(inputFilePath, outputFilePath, algorithm);

    return 0;
}
