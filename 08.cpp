#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

class Antenna {
public:
    Antenna(int x, int y, char frequency) : x(x), y(y), frequency(frequency) {}
    int x;
    int y;
    char frequency;
};

bool isInbound(int x, int y, int max_l, int max_c) {;
    if (x < 0 || x > max_l) { return false; }
    if (y < 0 || y > max_c) { return false; }
    return true;
}

vector<Antenna*> getSameFreqAntennas(set<Antenna*> antennas, char key) {
    vector<Antenna*> sameFreqAntennas;
    for (Antenna* a : antennas) {
        if (a->frequency == key) {
            sameFreqAntennas.push_back(a);
        }
    }
    return sameFreqAntennas;
}

void findAntinodes(vector<Antenna*>& same_f_antennas, set<tuple<int,int>>& occupied_pos, set<tuple<int, int>>& antinodes_pos, int max_l, int max_c) {
    for (size_t i = 0; i < same_f_antennas.size(); i++) {
        for (size_t j = i+1; j < same_f_antennas.size(); j++) {
            int dist_x = same_f_antennas[i]->x - same_f_antennas[j]->x;
            int dist_y = same_f_antennas[i]->y - same_f_antennas[j]->y;
            int x_i, x_j, y_i, y_j;

            x_i = same_f_antennas[i]->x + dist_x;
            x_j = same_f_antennas[j]->x - dist_x;

            y_i = same_f_antennas[i]->y + dist_y;
            y_j = same_f_antennas[j]->y - dist_y;

            if (isInbound(x_i, y_i, max_l, max_c)) {
                antinodes_pos.insert(make_tuple(x_i, y_i));
            }
            if (isInbound(x_j, y_j, max_l, max_c)) {
                antinodes_pos.insert(make_tuple(x_j, y_j));
            }
        }
    }
}

void findAntinodesWHarmonics(vector<Antenna*>& same_f_antennas, set<tuple<int, int>>& occupied_pos, set<tuple<int, int>>& antinodes_pos, int max_l, int max_c) {
    for (size_t i = 0; i < same_f_antennas.size(); i++) {
        for (size_t j = i + 1; j < same_f_antennas.size(); j++) {
            int x_i = same_f_antennas[i]->x;
            int x_j = same_f_antennas[j]->x;
            int y_i = same_f_antennas[i]->y;
            int y_j = same_f_antennas[j]->y;
            int dist_x = x_i - x_j;
            int dist_y = y_i - y_j;
            antinodes_pos.insert(make_tuple(x_i, y_i));
            antinodes_pos.insert(make_tuple(x_j, y_j));

            while (isInbound(x_i, y_i, max_l, max_c) || isInbound(x_j, y_j, max_l, max_c)) {
                x_i += dist_x;
                x_j -= dist_x;

                y_i += dist_y;
                y_j -= dist_y;

                if (isInbound(x_i, y_i, max_l, max_c)) {
                    antinodes_pos.insert(make_tuple(x_i, y_i));
                }
                if (isInbound(x_j, y_j, max_l, max_c)) {
                    antinodes_pos.insert(make_tuple(x_j, y_j));
                }
            }
        }
    }
}

int main_08() {
    ifstream input("08.txt");
    string line;
    int column = 0;
    int max_l = 0;
    int max_c = 0;
    set<Antenna*> antennas_set;
    set<tuple<int,int>> occupied_pos;
    set<char> keys;

    while (getline(input, line)) {
        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i] != '.') {
                Antenna* a = new Antenna(i, column, line[i]);
                antennas_set.insert(a);
                occupied_pos.insert(make_tuple(i, column));
                keys.insert(line[i]);
            }
        }
        column++;
        if (max_l == 0) { max_l = line.size() - 1; }
    }
    max_c = column - 1;

    set<tuple<int, int>> antinodes_pos;
    set<tuple<int, int>> antinodes_pos_w_harmonics;

    for (char key : keys) {
        vector<Antenna*> same_f_antennas = getSameFreqAntennas(antennas_set, key);
        findAntinodes(same_f_antennas, occupied_pos, antinodes_pos, max_l, max_c);
        findAntinodesWHarmonics(same_f_antennas, occupied_pos, antinodes_pos_w_harmonics, max_l, max_c);
    }

    for (tuple<int, int> pos : antinodes_pos) {
        cout << "(" << get<0>(pos) << "|" << get<1>(pos) << ")\n";
    }

    cout << "Part 1 : Number of unique locations that contains antinodes : " << antinodes_pos.size() << "\n";
    cout << "Part 2 : Number of unique locations that contains antinodes : " << antinodes_pos_w_harmonics.size() << "\n";
    return 0;
}
