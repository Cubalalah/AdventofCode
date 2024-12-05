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

    return line_vector;
}

bool isCorrect(string line) {
    vector<int> line_vector = vectorize(line);

   
}

int main() {
    ifstream input("05.txt");
    string line;
    vector<tuple<int,int>> rules;
    set<int> all_pages;

    while (getline(input, line) && line[0] != '\0') {
        int a = stoi(line.substr(0, line.find("|")));
        int b = stoi(line.substr(line.find("|")+1, line.size() - line.find("|")-1));
        rules.push_back(make_tuple(a, b));
        all_pages.insert(a);
        all_pages.insert(b);
    }

    int correct_updates_counter = 0;

    while (getline(input, line)) {
        if (isCorrect(line)) {
            correct_updates_counter++;
        }
    }

    cout << "Part 1 : Number of updates in the correct order : " << correct_updates_counter;
    return 0;
}
