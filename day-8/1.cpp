#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>

using namespace std;

void parseInput(const string &filePath, unordered_map<char, vector<pair<int,int>>>& mp, int& n, int& m) {
    ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
    }

    string line;
    int i = 0, j = 0;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        j = 0;
        char value;
        while (iss >> value) {
            if(value != '.') {
                mp[value].push_back({i,j});
            }
            j++;
        }
        i++;
    }
    m = i; n = j;
    inputFile.close();
}

void antinode(pair<int,int>& pr1, pair<int,int>& pr2, set<pair<int,int>>& st, const int& m, const int& n) {
    int x1 = pr1.first, y1 = pr1.second;
    int x2 = pr2.first, y2 = pr2.second;
    int newx = x2 + (x2 - x1);
    int newy = y2 + (y2 - y1);

    if(newx >= 0 && newx < m && newy >= 0 && newy < n) st.insert({newx, newy});
}

int findAntinodes(unordered_map<char, vector<pair<int,int>>>& mp, const int& m, const int& n) {
    set<pair<int,int>> st;
    int count = 0;
    for(auto x : mp) {
        auto antennas = x.second;

        for(int i = 0; i < antennas.size(); i++) {
            for(int j = 0; j < i; j++) {
                auto node1 = antennas[i];
                auto node2 = antennas[j];
                antinode(node1, node2, st, m, n);
                antinode(node2, node1, st, m, n);
            }
        }
    }

    return st.size();
}

int main() {
    unordered_map<char, vector<pair<int,int>>> mp;
    int m, n;
    parseInput("input.txt", mp, n, m);
    cout << findAntinodes(mp, m, n) << endl;
}