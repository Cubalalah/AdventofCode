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
    int n = 0;
    for (int i = 0; i < line.size(); i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < line[i]-'0'; j++) {
                disk_map.push_back(n);
            }
            n++;
        }
        else {
            for (int j = 0; j < line[i]-'0'; j++) {
                disk_map.push_back(-1);
            }
        }
    }
    return disk_map;
}

void rearrangeDiskMap_1(vector<int>& disk_map) {
    for (long long i = disk_map.size()-1; i >= 0; i--) {
        if (disk_map[i] != -1) {
            auto pos = find(disk_map.begin(), disk_map.end(), -1);
            if (pos < disk_map.begin() + i) {
                *pos = disk_map[i];
                disk_map.erase(disk_map.begin() + i);
            }
        }
        else {
            disk_map.erase(disk_map.begin() + i);
        }
    }
}

int searchEmptySpace(vector<int>& disk_map, int size, int maxi) {
    for (int i = 0; i <= maxi-size; i++) {
        bool match = true;
        for (int j = 0; j < size; j++) {
            if (disk_map[i + j] != -1) {
                match = false;
                break;
            }
        }
        if (match) {
            return i;
        }
    }
    return -1;
}

void moveFile(int begin, int end, int empty_space, vector<int>& disk_map) {
    for (int i = 0; i < end - begin; i++) {
        disk_map[empty_space + i] = disk_map[begin + i];
        disk_map[begin + i] = -1;
    }
}

void rearrangeDiskMap_2(vector<int>& disk_map, string line) {
    int k = disk_map.size();
    for (int j = line.size() - 1; j >= 0; j--) {
        int pos = line[j] - '0';
        if (j % 2 == 0 && pos != 0) {
            int empty_space = searchEmptySpace(disk_map, pos, k);
            if (empty_space != -1) {
                moveFile(k - pos, k, empty_space, disk_map);
            }
        }
        k -= pos;
    }
}

long long checkSum(vector<int>& vect) {
    long long sum = 0;
    for (long long i = 0; i < vect.size(); i++) {
        if (vect[i] != -1) {
            sum += i * vect[i];
        }
    }
    return sum;
}

int main_09() {
    ifstream input("09.txt");
    string line;

    getline(input, line);

    vector<int> disk_map = diskMapMaker(line);
    rearrangeDiskMap_1(disk_map);
    long long part1 = checkSum(disk_map);

    disk_map = diskMapMaker(line);
    rearrangeDiskMap_2(disk_map, line);

    long long part2 = checkSum(disk_map);

    cout << "Part 1 : Filesystem checksum : " << part1 << "\n";
    cout << "Part 2 : Filesystem checksum : " << part2 << "\n";
    return 0;
}
