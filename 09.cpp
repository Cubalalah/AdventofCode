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

vector<int> diskMapMaker(string line) {
    vector<int> disk_map;
    for (int i = 0; i < line.size(); i++) {
        int n = (i / 2) % 10;
        if (i % 2 == 0) {
            for (size_t j = 0; j < line[i]-'0'; j++) {
                disk_map.push_back(n);
            }
        }
        else {
            for (size_t j = 0; j < line[i]-'0'; j++) {
                disk_map.push_back(-1);
            }
        }
    }
    return disk_map;
}

void rearrangeDiskMap(vector<int>& disk_map) {
    for (int i = disk_map.size()-1; i > -1; i--) {
        if (disk_map[i] != -1 && find(disk_map.begin(), disk_map.end(), -1) != disk_map.end()) {
            auto pos = find(disk_map.begin(), disk_map.end(), -1);
            *pos = disk_map[i];
            disk_map.erase(disk_map.begin() + i);
        }
    }
}

long long checkSum(vector<int>& vect) {
    long long sum = 0;
    for (long long i = 0; i < vect.size(); i++) {
        sum += i * vect[i];
    }
    return sum;
}

int main() {
    ifstream input("09.txt");
    string line;

    getline(input, line);

    vector<int> disk_map = diskMapMaker(line);
    rearrangeDiskMap(disk_map);
    long long part1 = checkSum(disk_map);

    cout << "Part 1 : Filesystem checksum : " << part1 << "\n";
    return 0;
}
