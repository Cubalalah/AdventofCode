#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

void addDict(unordered_map<long long, long long>& map, long long value, long long n = 1) {
    if (map.find(value) != map.end()) {
        map[value]+=n;
    }
    else {
        map.insert({ value, n });
    }
}

unordered_map<long long, long long> mapize(string line) {
    size_t initialPos = 0;
    size_t space_pos = line.find(" ");
    unordered_map<long long, long long> stones;

    while (space_pos != std::string::npos) {
        addDict(stones, stoi(line.substr(initialPos, space_pos - initialPos)));
        initialPos = space_pos + 1;
        space_pos = line.find(" ", initialPos);
    }

    addDict(stones, stoi(line.substr(initialPos, stones.size() - initialPos)));
    return stones;
}

unordered_map<long long, long long> transformStones(unordered_map<long long, long long>& stones) {
    unordered_map<long long, long long> new_stones;
    for (pair<long long, long long> stone : stones) {
        if (stone.first == 0) {
            addDict(new_stones, 1, stone.second);
        }
        else if (to_string(stone.first).size() % 2 == 0) {
            long long first_half = stoi(to_string(stone.first).substr(0, to_string(stone.first).size() / 2));
            long long second_half = stoi(to_string(stone.first).substr(to_string(stone.first).size() / 2));
            addDict(new_stones, first_half, stone.second);
            addDict(new_stones, second_half, stone.second);
        }
        else {
            addDict(new_stones, stone.first*2024, stone.second);
        }
    }
    return new_stones;
}


void afficher(unordered_map<long long, long long>& stones) {
    for (pair<long long,long long> stone : stones) {
        cout << "(" << stone.first << " " << stone.second << ")" << "\n";
    }
}


long long sizeMap(unordered_map<long long, long long>& stones) {
    long long output = 0;
    for (pair<long long, long long> stone : stones) {
        output += stone.second;
    }
    return output;
}

int main() {
    ifstream input("11.txt");
    string line;
    getline(input, line);
    unordered_map<long long, long long> stones = mapize(line);
    for (size_t i = 1; i <= 25; i++) {
        stones = transformStones(stones);
    }
    cout << "Part 1 : Number of stones after 25 blinks : " << sizeMap(stones) << "\n";
    for (size_t i = 26; i <= 75; i++) {
        stones = transformStones(stones);
    }
    cout << "Part 2 : Number of stones after 75 blinks : " << sizeMap(stones) << "\n";

    cout << "\n";
    afficher(stones);

    return 0;
}
