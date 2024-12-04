#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

bool isInt(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

bool isCorrectMul(string line) {
    int comma_loc = line.find(",");
    if (comma_loc > 7 || !isInt(line.substr(4, comma_loc - 4))) {
        return false;
    }
    int bracket_loc = line.find(")");
    if (bracket_loc - comma_loc > 4 || !isInt(line.substr(comma_loc + 1, bracket_loc - comma_loc - 1))) {
        return false;
    }
    return true;
}

vector<tuple<int, int>> findMul(string line) {
    size_t initialPos = 0;
    size_t mul_pos = line.find("mul(");
    vector<tuple<int, int>> mul_vector;

    while (mul_pos != std::string::npos) {
        if (isCorrectMul(line.substr(mul_pos, 12))) {
            int first_digit = stoi(line.substr(line.find("(", mul_pos) + 1, line.find(",", mul_pos)));
            int second_digit = stoi(line.substr(line.find(",", mul_pos) + 1, line.find(")", mul_pos)));
            mul_vector.push_back(make_tuple(first_digit, second_digit));
        }
        initialPos = mul_pos + 1;
        mul_pos = line.find("mul(", initialPos);
    }

    return mul_vector;
}

vector<tuple<int, int>> findMulWDoDont(string line) {
    size_t do_pos = 0;
    size_t mul_pos = line.find("mul(", do_pos);
    size_t dont_pos = line.find("don't()", do_pos);
    vector<tuple<int, int>> mul_vector;

    while (mul_pos != std::string::npos) {
        if (dont_pos > mul_pos) {
            if (isCorrectMul(line.substr(mul_pos, 12))) {
                int first_digit = stoi(line.substr(line.find("(", mul_pos) + 1, line.find(",", mul_pos)));
                int second_digit = stoi(line.substr(line.find(",", mul_pos) + 1, line.find(")", mul_pos)));
                mul_vector.push_back(make_tuple(first_digit, second_digit));
            }
            do_pos = mul_pos + 1;
        }
        else {
            do_pos = line.find("do()", dont_pos);
            dont_pos = line.find("don't()", do_pos);
        }
        mul_pos = line.find("mul(", do_pos);
    }

    return mul_vector;
}

int main_03() {
    ifstream input("03.txt");
    string line;
    string complete_line;
    int part1 = 0;
    int part2 = 0;

    while (getline(input, line)) {
        complete_line += line;
    }

    for (tuple<int, int> mul : findMul(complete_line)) {
        part1 += get<0>(mul) * get<1>(mul);
    }
    for (tuple<int, int> mul : findMulWDoDont(complete_line)) {
        part2 += get<0>(mul) * get<1>(mul);
    }

    cout << "Part 1 : Result of the multiplications : " << part1 << "\n";
    cout << "Part 2 : Result of the multiplications : " << part2 << "\n";

    return 0;
}
