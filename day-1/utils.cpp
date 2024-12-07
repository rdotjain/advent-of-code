#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool readIntegerPairsFromFile(const std::string &filePath, std::vector<int> &left, std::vector<int> &right) {
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int leftVal, rightVal;
        if (iss >> leftVal >> rightVal) {
            left.push_back(leftVal);
            right.push_back(rightVal);
        } else {
            std::cerr << "Warning: Skipping malformed line -> " << line << std::endl;
        }
    }
    inputFile.close();
    return true;
}
