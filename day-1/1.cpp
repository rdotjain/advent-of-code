#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include "utils.h"

using namespace std;


int solve(vector<int>& left, vector<int>&right) {
    priority_queue<int> pql;
    priority_queue<int> pqr;
    
    for(auto i : left) {
        pql.push(i);
    }
    
    for(auto i : right) {
        pqr.push(i);
    }
    
    int dist = 0;
    
    while(!pql.empty() || !pqr.empty()) {
        int l = pql.top(); pql.pop();
        int r = pqr.top(); pqr.pop();
        dist += abs(l-r);
    }
    
    return dist;
}

int main() {
    vector<int> left, right;
    readIntegerPairsFromFile("sample.txt", left, right);

    int dist = solve(left, right);
    cout << dist;

    return 0;
}
