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
#include <climits>

using namespace std;

vector<long long> vect(string line) {
    size_t initialPos = 0;
    size_t space_pos = line.find(" ");
    vector<long long> stones;

    while (space_pos != std::string::npos) {
        stones.push_back(stoi(line.substr(initialPos, space_pos - initialPos)));
        initialPos = space_pos + 1;
        space_pos = line.find(" ", initialPos);
    }

    stones.push_back(stoi(line.substr(initialPos, stones.size() - initialPos)));

    return stones;
}

void transformStones(vector<long long>& stones) {
    int i = 0;
    while (i < stones.size()) {
        if (stones[i] == 0) {
            stones[i] = 1;
        }
        else if (to_string(stones[i]).size() % 2 == 0) {
            long long first_half = stoi(to_string(stones[i]).substr(0, to_string(stones[i]).size() / 2));
            long long second_half = stoi(to_string(stones[i]).substr(to_string(stones[i]).size() / 2));
            stones[i] = first_half;
            stones.insert(stones.begin() + i, second_half);
            i++;
        }
        else {
            stones[i] *= 2024;
        }
        i++;
    }
}

void afficher(vector<long long>& stones) {
    for (long long stone : stones) {
        cout << stone << " ";
    }
    cout << "\n";
}

int main() {
    ifstream input("11.txt");
    string line;
    getline(input, line);
    vector<long long> stones = vect(line);
    for (size_t i = 1; i <= 25; i++) {
        cout << i << "\n";
        transformStones(stones);
    }
    cout << "Part 1 : Number of stones after 25 blinks : " << stones.size();

    return 0;
}
