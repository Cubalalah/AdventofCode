#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void split(const std::string& line, vector<int>& report)
{
    size_t pos = line.find(" ");
    size_t initialPos = 0;
    report.clear();

    // Decompose statement
    while (pos != std::string::npos) {
        report.push_back(stoi(line.substr(initialPos, pos - initialPos)));
        initialPos = pos + 1;

        pos = line.find(" ", initialPos);
    }

    // Add the last one
    report.push_back(stoi(line.substr(initialPos, std::min(pos, line.size()) - initialPos + 1)));
}

bool isSafe(vector<int> init_report) {
    vector<int> inc_report = init_report;
    sort(inc_report.begin(), inc_report.end(), [](int a, int b) { return a < b; });

    vector<int> dec_report = init_report;
    sort(dec_report.begin(), dec_report.end(), [](int a, int b) { return a > b; });
    if (init_report == inc_report || init_report == dec_report) {
        for (size_t i = 1; i < init_report.size(); i++) {
            if (abs(init_report[i] - init_report[i - 1]) > 3 || abs(init_report[i] - init_report[i - 1]) < 1) {
                return false;
            }
        }
        return true;
    }
    else {
        return false;
    }
}

bool isSafeWithProblemDampener(vector<int> init_report) {
    for (size_t i = 0; i < init_report.size(); i++) {
        vector<int> new_report = init_report;
        new_report.erase(new_report.begin() + i);
        if (isSafe(new_report)) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream input("02.txt");
    string line;
    int part_1_counter = 0;
    int part_2_counter = 0;

    while (getline(input, line)) {
        vector<int> init_report;
        split(line, init_report);
        
        if (isSafe(init_report)) {
           part_1_counter++;
           part_2_counter++;
        }
        else {
            if (isSafeWithProblemDampener(init_report)) {
                part_2_counter++;
            }
        }
    }
    cout << "Part 1 : Total number of safe reports : " << part_1_counter << "\n";
    cout << "Part 1 : Total number of safe reports : " << part_2_counter << "\n";

    return 0;
}
