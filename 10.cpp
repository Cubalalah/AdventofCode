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

bool isInbound(int x, int y, vector<vector<int>>& const map) {
    if (x < 0 || x >= map[0].size()) {
        return false;
    }
    if (y < 0 || y >= map.size()) {
        return false;
    }
    return true;
}

set<pair<int, int>> numbersNearby(int number, pair<int, int> location, vector<vector<int>>& const map, vector<pair<int,int>>& const directions) {
    int y = location.first;
    int x = location.second;
    set<pair<int, int>> number_loc;
    for (pair<int, int> dir : directions) {
        int new_x = x + dir.first;
        int new_y = y + dir.second;
        if (isInbound(new_x, new_y, map) && map[new_y][new_x] == number) {
            number_loc.insert(make_pair(new_y, new_x));
        }
    }
    return number_loc;
}

void findSummits(pair<int,int> t, vector<vector<int>>& const map, vector<pair<int, int>>& const directions, vector<pair<int, int>>& summits) {
    int y = t.first;
    int x = t.second;
    if (map[y][x] == 9) {
        summits.push_back(t);
    }
    else {
        set<pair<int, int>> next_numbers = numbersNearby(map[y][x] + 1, t, map, directions);
        for (pair<int, int> n : next_numbers) {
            findSummits(n, map, directions, summits);
        }
    }
}

tuple<int,int> scoreCalculation(pair<int, int> t, vector<vector<int>>& const map) {
    vector<pair<int, int>> summits;
    set<pair<int, int>> set_summits;
    vector<pair<int, int>> directions = { make_pair(1,0), make_pair(0,1), make_pair(-1,0), make_pair(0,-1) };
    findSummits(t, map, directions, summits);
    for (pair<int, int> summit : summits) {
        set_summits.insert(summit);
    }
    return make_tuple(set_summits.size(), summits.size());
}

int main_10() {
    ifstream input("10.txt");
    string line;
    vector<vector<int>> map;
    set<pair<int, int>> trailheadsPos;
    while (getline(input, line)) {
        vector<int> map_line;
        for (int i = 0; i < line.size(); i++) {
            int place = line[i] - '0';
            if (place == 0) {
                trailheadsPos.insert(make_pair(map.size(), i));
            }
            map_line.push_back(place);
        }
        map.push_back(map_line);
    }

    int part1 = 0;
    int part2 = 0;
    for (pair<int, int> trailhead : trailheadsPos) {
        tuple<int, int> score = scoreCalculation(trailhead, map);
        part1 += get<0>(score);
        part2 += get<1>(score);
    }

    cout << "Part 1 : Sum of the score of all trailheads : " << part1 << "\n";
    cout << "Part 2 : Sum of the score of all trailheads : " << part2 << "\n";
    return 0;
}
