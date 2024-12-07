#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string canonicalRule(int a, int b) {
    return to_string(a) + "|" + to_string(b);
}

bool ruleExists(int a, int b, const unordered_set<string>& rules) {
    string rule = canonicalRule(a, b);
    string rev_rule = canonicalRule(b, a);
    if(rules.find(rule) != rules.end()) return true;
    if(rules.find(rev_rule) != rules.end()) return false;
    return false;
}

int main() {
    unordered_set<string> rules;
    vector<vector<int>> updates;

    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Failed to open the file" << endl;
        return 1;
    }

    // Parse file
    string line;
    bool isParsingRules = true;

    while (getline(file, line)) {
        if (line.empty()) {
            isParsingRules = false;
            continue;
        }

        if (isParsingRules) {
            rules.insert(line); // Directly add the rule to the set
        } else {
            vector<int> updateRow;
            istringstream ss(line);
            int value;
            char delimiter;
            while (ss >> value) {
                updateRow.push_back(value);
                ss >> delimiter; // Consume delimiter if present
            }
            updates.push_back(updateRow);
        }
    }

    file.close();

    int middleSum = 0, middleSumIncorrect = 0;

    for (auto& update : updates) {
        bool isValid = true;

        // Check validity of updates
        for (size_t i = 0; i < update.size() - 1; ++i) {
            if (!ruleExists(update[i], update[i+1], rules)) {
                isValid = false;
                break;
            }
        }

        if (isValid) {
            middleSum += update[update.size() / 2];
        } else {
            // Correct the sequence using a custom comparator
            sort(update.begin(), update.end(), [&rules](int a, int b) {
                return ruleExists(a, b, rules);
            });
            middleSumIncorrect += update[update.size() / 2];
        }
    }

    cout << "Sum of middle page numbers: " << middleSum << endl;
    cout << "Sum of corrected middle page numbers: " << middleSumIncorrect << endl;

    return 0;
}
