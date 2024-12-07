#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

void readDataIntoVectorOfVectors(const string &filePath, vector<vector<int>> &data) {
    ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        vector<int> row;
        int value;
        while (iss >> value) {
            row.push_back(value);
        }
        data.push_back(row);
    }
    inputFile.close();
}

// flag 1: decreasing sequence 
// flag 2: increasing sequence
// flag 3: 1 <= |curr_diff| <= 3 

bool is_safe(vector<int>& report)
{
    int flag1, flag2, flag3;
    flag1 = flag2 = flag3 = 1;
    for(int i = 0; i < report.size() - 1; i++){
        int diff = abs(report[i] - report[i + 1]);
        flag1 = flag1 && (report[i] > report[i + 1]);
        flag2 = flag2 && (report[i] < report[i + 1]);
        flag3 = flag3 && (diff >= 1 && diff <= 3);
        if( !((flag1 || flag2) && flag3))
            return false;
    }
    return true;
}

int solve(vector<vector<int>> &data) {
    int count = 0;

    for(auto report : data) {
        if(is_safe(report)) {
            count++;
            continue;
        }
        for(int i = 0; i < report.size(); i++) {
            vector<int>temp = report;
            temp.erase(temp.begin()+i);
            if(is_safe(temp)) {
                count++;
                break;
            }
        }
    }

    return count;
}

int main() {
    vector<vector<int>> data;
    readDataIntoVectorOfVectors("input.txt", data);

    int count = solve(data);
    cout << count << endl;;

    return 0;
}