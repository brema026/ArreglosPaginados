#include "generator.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

void generateFile(size_t size, const std::string& outputFilePath) {
    std::ofstream outFile(outputFilePath, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << outputFilePath << std::endl;
        return;
    }

    size_t numIntegers = size / sizeof(int);
    std::srand(std::time(0));

    for (size_t i = 0; i < numIntegers; ++i) {
        int value = std::rand();
        outFile.write(reinterpret_cast<char*>(&value), sizeof(value));
    }

    outFile.close();
    std::cout << "File generated successfully: " << outputFilePath << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: generator -size <SIZE> -output <OUTPUT FILE PATH>" << std::endl;
        return 1;
    }

    size_t size;
    std::string outputFilePath;

    if (std::string(argv[1]) == "-size") {
        if (std::string(argv[2]) == "SMALL") {
            size = 512 * 1024 * 1024;  // 512 MB
        } else if (std::string(argv[2]) == "MEDIUM") {
            size = 1 * 1024 * 1024 * 1024;  // 1 GB
        } else if (std::string(argv[2]) == "LARGE") {
            size = 2048LL * 1024 * 1024;  // 2 GB
        } else {
            std::cerr << "Invalid size parameter." << std::endl;
            return 1;
        }

        outputFilePath = argv[4];
        generateFile(size, outputFilePath);
    } else {
        std::cerr << "Invalid option." << std::endl;
        return 1;
    }

    return 0;
}
