#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void parseInput(const string& filePath, vector<vector<char>>& map, pair<int, int>& guard) {
    ifstream inputFile(filePath);

    if (!inputFile) {
        cerr << "Error: Could not open the file!" << endl;
        exit(1);
    }

    string line;
    int row = 0;

    while (getline(inputFile, line)) {
        vector<char> currentRow(line.begin(), line.end());
        for (int col = 0; col < currentRow.size(); ++col) {
            if (currentRow[col] == '^') {
                guard = {row, col};
            }
        }
        map.push_back(std::move(currentRow));
        ++row;
    }
}

// Rotate the direction vector 90 degrees clockwise
void rotateRight(pair<int, int>& dir) {
    dir = {dir.second, -dir.first};
}

// Check if the guard is within bounds of the map
bool isInBounds(const pair<int, int>& guard, int size) {
    return guard.first > 0 && guard.second > 0 && guard.first < size - 1 && guard.second < size - 1;
}

void solve(vector<vector<char>>& map, pair<int, int>& guard) {
    int n = map.size();
    pair<int, int> dir = {-1, 0}; // Initial direction (up)
    int count = 1;

    map[guard.first][guard.second] = 'X';

    while (isInBounds(guard, n)) {
        int nr = guard.first + dir.first;
        int nc = guard.second + dir.second;

        if (map[nr][nc] == '#') {
            rotateRight(dir); // Change direction if obstacle encountered
        } else {
            guard = {nr, nc};

            if (map[guard.first][guard.second] != 'X') {
                map[guard.first][guard.second] = 'X';
                ++count;
            }
        }
    }

    cout << count << endl;
}

int main() {
    vector<vector<char>> map;
    pair<int, int> guard;

    parseInput("input.txt", map, guard);
    solve(map, guard);

    return 0;
}
