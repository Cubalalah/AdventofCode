#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <algorithm>

using namespace std;

int main() {
    ifstream input("05.txt");
    string line;
    vector<tuple<int,int>> rules;

    while (getline(input, line) && line[0] != '\0') {
        cout << line;
        int a = stoi(line.substr(0, line.find("|")));
        int b = stoi(line.substr(line.find("|")+1, line.size() - line.find("|")-1));
        rules.push_back(make_tuple(a, b));
    }

    vector<int> ordered_pages;

    for (tuple<int, int> rule : rules) {
        int a = get<0>(rule);
        int b = get<1>(rule);
        auto pos_a = find(ordered_pages.begin(), ordered_pages.end(), a);
        auto pos_b = find(ordered_pages.begin(), ordered_pages.end(), b);
        if (pos_a == pos_b) {

        }
    }

    return 0;
}
