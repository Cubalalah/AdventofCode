#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <algorithm>

using namespace std;

bool isValidCoordinates(int x, int y, vector<vector<char>> table) {
    if (x < 0 || x >= table[0].size()) {
        return false;
    }
    if (y < 0 || y >= table.size()) {
        return false;
    }
    return true;
}

bool isXMAS(int x, int y, vector<vector<char>> table, tuple<int, int> direction) {
    if (table[x][y] == 'X') {
        x += get<0>(direction);
        y += get<1>(direction);

        if (isValidCoordinates(x, y, table) && table[x][y] == 'M') {
            x += get<0>(direction);
            y += get<1>(direction);

            if (isValidCoordinates(x, y, table) && table[x][y] == 'A') {
                x += get<0>(direction);
                y += get<1>(direction);

                if (isValidCoordinates(x, y, table) && table[x][y] == 'S') {
                    return true;
                }
            }
        }
    }
    else if (table[x][y] == 'S') {
        x += get<0>(direction);
        y += get<1>(direction);

        if (isValidCoordinates(x, y, table) && table[x][y] == 'A') {
            x += get<0>(direction);
            y += get<1>(direction);

            if (isValidCoordinates(x, y, table) && table[x][y] == 'M') {
                x += get<0>(direction);
                y += get<1>(direction);

                if (isValidCoordinates(x, y, table) && table[x][y] == 'X') {
                    return true;
                }
            }
        }
    }
    return false;
}

bool isX_MAS(int x, int y, vector<vector<char>> table) {
    if (table[x][y] == 'A') {
        if (isValidCoordinates(x - 1, y - 1, table) && isValidCoordinates(x + 1, y + 1, table)) {
            if (table[x - 1][y - 1] == 'M' && table[x + 1][y + 1] == 'S' && table[x - 1][y + 1] == 'M' && table[x + 1][y - 1] == 'S') {
                return true;
            }
            if (table[x - 1][y - 1] == 'M' && table[x + 1][y + 1] == 'S' && table[x - 1][y + 1] == 'S' && table[x + 1][y - 1] == 'M') {
                return true;
            }
            if (table[x - 1][y - 1] == 'S' && table[x + 1][y + 1] == 'M' && table[x - 1][y + 1] == 'M' && table[x + 1][y - 1] == 'S') {
                return true;
            }
            if (table[x - 1][y - 1] == 'S' && table[x + 1][y + 1] == 'M' && table[x - 1][y + 1] == 'S' && table[x + 1][y - 1] == 'M') {
                return true;
            }
        }
    }
    return false;
}

int main_04() {
    ifstream input("04.txt");
    string line;
    vector<vector<char>> table;

    while (getline(input, line)) {
        vector<char> row;
        for (char letter : line) {
            row.push_back(letter);
        }
        table.push_back(row);
    }

    vector<tuple<int, int>> directions = { make_tuple(1,0), make_tuple(1,1), make_tuple(0,1), make_tuple(-1,1) };

    int numberOfXMAS = 0;
    int numberOfX_MAS = 0;

    for (size_t i = 0; i < table.size(); i++) {
        for (size_t j = 0; j < table[i].size(); j++) {
            for (tuple<int, int> direction : directions) {
                if (isXMAS(j, i, table, direction)) {
                    numberOfXMAS++;
                }
            }
            if (isX_MAS(j, i, table)) {
                numberOfX_MAS++;
            }
        }
    }

    cout << "Part 1 : Number of appearances of XMAS : " << numberOfXMAS << "\n";
    cout << "Part 2 : Number of appearances of X-MAS : " << numberOfX_MAS << "\n";

    return 0;
}
