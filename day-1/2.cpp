#include <vector>
#include <iostream>
#include <map>
#include "utils.h"

using namespace std;

int solve(vector<int>& left, vector<int>&right) {
    unordered_map<int,int> mp;
    for(auto i : left) {
        mp[i] = 0;
    }

    for(auto i : right) {
        if(mp.find(i) != mp.end()) mp[i]++;
    }

    int sum = 0;
    for(auto i : left) {
        sum += i * mp[i];
    }

    return sum;
}

int main() {
    vector<int> left, right;
    readIntegerPairsFromFile("input.txt", left, right);

    int dist = solve(left, right);
    cout << dist;

    return 0;
}