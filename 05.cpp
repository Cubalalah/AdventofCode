#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <set>
#include <algorithm>

using namespace std;

vector<int> vectorize(string line) {
    size_t initialPos = 0;
    size_t comma_pos = line.find(",");
    vector<int> line_vector;

    while (comma_pos != std::string::npos) {
        line_vector.push_back(stoi(line.substr(initialPos, comma_pos - initialPos)));
        initialPos = comma_pos + 1;
        comma_pos = line.find(",", initialPos);
    }

    line_vector.push_back(stoi(line.substr(initialPos, line_vector.size() - initialPos)));

    return line_vector;
}

bool isCorrect(vector<int> line_vector, vector<tuple<int, int>> rules) {
    for (int i = 1; i < line_vector.size(); i++) {
        if (find(rules.begin(), rules.end(), make_tuple(line_vector[i-1], line_vector[i])) == rules.end()) {
            return false;
        }
    }
    return true;
}

vector<int> becomeCorrect(vector<int> line_vector, vector<tuple<int, int>> rules) {
    int i = 1;
    while (!isCorrect(line_vector, rules)) {
        if (find(rules.begin(), rules.end(), make_tuple(line_vector[i - 1], line_vector[i])) == rules.end()) {
            auto temp = line_vector[i];
            line_vector[i] = line_vector[i - 1];
            line_vector[i - 1] = temp;
            i = 1;
        }
        else {
            i++;
        }
    }
    return line_vector;
}

int main() {
    ifstream input("05.txt");
    string line;
    vector<tuple<int,int>> rules;

    while (getline(input, line) && line[0] != '\0') {
        int a = stoi(line.substr(0, line.find("|")));
        int b = stoi(line.substr(line.find("|")+1, line.size() - line.find("|")-1));
        rules.push_back(make_tuple(a, b));
    }

    int part1 = 0;
    int part2 = 0;

    while (getline(input, line)) {
        vector<int> line_vector = vectorize(line);
        if (isCorrect(line_vector, rules)) {
            part1 += line_vector[line_vector.size()/2];
        }
        else {
            vector<int> new_vector = becomeCorrect(line_vector, rules);
            part2 += new_vector[new_vector.size() / 2];
        }
    }

    cout << "Part 1 : Sum of middle page numbers of updates in the correct order : " << part1 << "\n";
    cout << "Part 2 : Sum of middle page numbers of updates in the incorrect order : " << part2;
    return 0;
}
