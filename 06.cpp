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

void getValues(ifstream& input, int& max_l, int& max_c, tuple <int, int>& guard_pos, set<tuple<int, int>>& obstacles_pos) {
    
    int column = 0;
    string line;

    while (getline(input, line)) {
        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i] == '^') {
                guard_pos = make_tuple(column, i);
            }
            else if (line[i] == '#') {
                obstacles_pos.insert(make_tuple(column, i));
            }
        }
        column++;
        if (max_l == 0) { max_l = line.size() - 1; }
    }
    max_c = column - 1;
}

bool isInbound(tuple<int,int> pos, int max_l, int max_c) {
    int line = get<0>(pos);
    int column = get<1>(pos);
    if (line < 0 || line > max_l) { return false; }
    if (column < 0 || column > max_c) { return false; }
    return true;
}

bool isObjectinSet(int l, int c, set<tuple<int, int>>& const object_set) {
    if (find(object_set.begin(), object_set.end(), make_tuple(l, c)) != object_set.end()) {
        return true;
    }
    return false;
}

bool isObjectinSet(int l, int c, int d, set<tuple<int, int, int>>& const object_set) {
    if (find(object_set.begin(), object_set.end(), make_tuple(l, c, d)) != object_set.end()) {
        return true;
    }
    return false;
}

bool isObject(int l, int c, tuple<int, int> object) {
    if (make_tuple(l,c)==object) {
        return true;
    }
    return false;
}

bool isLoop(set<tuple<int, int>>& const obstacles_pos, tuple<int,int> guard_pos, int max_l, int max_c) {
    set<tuple<int, int, int>> already_seen;
    vector<tuple<int, int>> directions = { make_tuple(-1,0), make_tuple(0,1), make_tuple(1,0), make_tuple(0,-1) };
    int curr_dir = 0;
    int curr_l = get<0>(guard_pos);
    int curr_c = get<1>(guard_pos);
    int next_l = curr_l + get<0>(directions[curr_dir]);
    int next_c = curr_c + get<1>(directions[curr_dir]);

    while (isInbound(make_tuple(curr_l, curr_c), max_l, max_c)) {
        if (isObjectinSet(curr_l, curr_c, curr_dir, already_seen)) {
            return true;
        }
        if (!isObjectinSet(next_l, next_c, obstacles_pos)) {
            already_seen.insert(make_tuple(curr_l, curr_c, curr_dir));
            curr_l = next_l;
            curr_c = next_c;
            next_l += get<0>(directions[curr_dir]);
            next_c += get<1>(directions[curr_dir]);
        }
        else {
            curr_dir = (curr_dir + 1) % 4;
            next_l = curr_l + get<0>(directions[curr_dir]);
            next_c = curr_c + get<1>(directions[curr_dir]);
        }
    }
    return false;
}

int main_06() {
    ifstream input("06.txt");
    int max_l = 0;
    int max_c = 0;
    tuple<int, int> guard_pos;
    set<tuple<int, int>> obstacles_pos;

    getValues(input, max_l, max_c, guard_pos, obstacles_pos);

    vector<tuple<int, int>> directions = { make_tuple(-1,0), make_tuple(0,1), make_tuple(1,0), make_tuple(0,-1) };
    int curr_dir = 0;

    int curr_l = get<0>(guard_pos);
    int curr_c = get<1>(guard_pos);
    int next_l = curr_l + get<0>(directions[curr_dir]);
    int next_c = curr_c + get<1>(directions[curr_dir]);

    set<tuple<int, int>> distinct_pos;

    while (isInbound(make_tuple(curr_l, curr_c), max_l, max_c)) {
        distinct_pos.insert(make_tuple(curr_l, curr_c));

        if (!isObjectinSet(next_l, next_c, obstacles_pos)) {
            curr_l = next_l;
            curr_c = next_c;
            next_l += get<0>(directions[curr_dir]);
            next_c += get<1>(directions[curr_dir]);
        }
        else {
            curr_dir = (curr_dir + 1) % 4;
            next_l = curr_l + get<0>(directions[curr_dir]);
            next_c = curr_c + get<1>(directions[curr_dir]);
        }
    }

    int obstruction_counter = 0;
    int i = 0;

    for (tuple<int, int> new_obstacle : distinct_pos) {
        obstacles_pos.insert(new_obstacle);
        if ((new_obstacle != guard_pos) && (isLoop(obstacles_pos, guard_pos, max_l, max_c))) {
            obstruction_counter++;
        }
        obstacles_pos.erase(new_obstacle);
        i++;
        cout << "Number of obstruction : " << obstruction_counter << " ("<<i<<"/"<<distinct_pos.size()<<")\n";
    }


    cout << "Position of the guard : " << get<0>(guard_pos) << " | " << get<1>(guard_pos) << "\n";
    cout << "Part 1 : Number of distinct positions visited : " << distinct_pos.size() << "\n";
    cout << "Part 2 : Number of possible obstruction positions : " << obstruction_counter << "\n";

    return 0;
}
