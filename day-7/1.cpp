#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

void parseInput(const string& filePath, unordered_map<long long int, vector<int>>& equations) {
    ifstream inputFile(filePath);

    if (!inputFile) {
        cerr << "Error: Could not open the file!" << endl;
        exit(1);
    }

    string line;
    while(getline(inputFile, line)) {
        istringstream iss(line);
        long long int key; char colon;
        iss >> key >> colon;

        vector<int> values;
        int value;
        while(iss >> value) {
            values.push_back(value);
        }

        equations[key] = values;
    }
}

bool check(int i, long long int current, const long long int test_value, vector<int>& equation, int n) {
    if(i == n ||  current > test_value) {
        return current == test_value;
    }

    return check(i+1, current * equation[i], test_value, equation, n) 
    || check(i+1, current + equation[i], test_value, equation, n)
    || check(i+1, current * pow(10, floor(log10(equation[i])) + 1)+equation[i], test_value, equation, n);
}

int main() {
    unordered_map<long long int, vector<int>> equations;
    parseInput("input.txt", equations);
    long long int sum = 0;
    for(auto i : equations) {
        long long int test_value = i.first;
        vector<int> value = i.second;
        if(check(1, value[0], test_value, value, value.size()))
            sum += test_value;
    }
    cout << sum << endl;
}

