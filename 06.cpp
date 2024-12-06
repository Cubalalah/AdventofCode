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

vector<string> vectorize(string line) {
    vector<string> line_vector;

    for (int i = 0; i < line.size(); i++) {
        line_vector.push_back(line.substr(i, 1));
    }

    return line_vector;
}

bool isValid(tuple<int,int> pos, vector<vector<string>> map) {
    int line = get<0>(pos);
    int column = get<1>(pos);
    if (line < 0 || line >= map.size()) { return false; }
    if (column < 0 || column >= map[0].size()) { return false; }
    return true;
}

void printMap(vector<vector<string>> map) {
    for (vector<string> line : map) {
        for (string x : line) {
            cout << x;
        }
        cout << "\n";
    }
}

int main() {
    ifstream input("06.txt");
    string line;
    vector<vector<string>> map;
    tuple <int, int> guard_pos;

    while (getline(input, line)) {
        map.push_back(vectorize(line));
        if (find(line.begin(), line.end(), '^') != line.end()) {
            guard_pos = make_tuple(map.size()-1, line.find("^"));
        }
    }

    vector<tuple<int, int>> directions = { make_tuple(-1,0), make_tuple(0,1), make_tuple(1,0), make_tuple(0,-1) };
    int curr_dir = 0;
    tuple<int, int> next_guard_pos = make_tuple(get<0>(guard_pos) + get<0>(directions[curr_dir]), get<1>(guard_pos) + get<1>(directions[curr_dir]));

    vector<tuple<int, int>> distinct_pos;
    distinct_pos.push_back(guard_pos);
    map[get<0>(guard_pos)][get<1>(guard_pos)] = "X";
    int distinct_pos_counter = 1;

    while (isValid(next_guard_pos, map)) {
        int next_l = get<0>(next_guard_pos);
        int next_c = get<1>(next_guard_pos);
        if (map[next_l][next_c] == "#") {
            curr_dir++;
            if (curr_dir > 3) {
                curr_dir = 0;
            }
        }
        else {
            if (map[next_l][next_c] == ".") {
                map[next_l][next_c] = "X";
                distinct_pos_counter++;
                distinct_pos.push_back(next_guard_pos);
            }
            guard_pos = next_guard_pos;
        }
        next_guard_pos = make_tuple(get<0>(guard_pos) + get<0>(directions[curr_dir]), get<1>(guard_pos) + get<1>(directions[curr_dir]));
    }

    printMap(map);

    cout << "Position of the guard : " << get<0>(guard_pos) << " | " << get<1>(guard_pos) << "\n";
    cout << "Part 1 : Number of distinct positions visited : " << distinct_pos_counter;
    return 0;
}
