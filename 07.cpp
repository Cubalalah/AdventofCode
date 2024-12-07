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

long long concatenate(long long a, long long b) {
    string s1 = to_string(a);
    string s2 = to_string(b);
    string s = s1 + s2;
    return stoll(s);
}

bool findEquation(long long result, vector<int> numbers, long long var) {
    if (numbers.size() == 1) {
        if (var + numbers[0] == result || var * numbers[0] == result) {
            return true;
        }
        return false;
    }
    long long new_var = numbers[0];
    vector<int> new_numbers(numbers.begin() + 1, numbers.end());
    if (var * new_var <= result) {
        if (findEquation(result, new_numbers, var * new_var)) {
            return true;
        }
    }
    if (var + new_var <= result) {
        if (findEquation(result, new_numbers, var + new_var)) {
            return true;
        }
    }
    return false;
}

bool findEquation_2(long long result, vector<int> numbers, long long var) {
    if (numbers.size() == 1) {
        if (var + numbers[0] == result || var * numbers[0] == result || concatenate(var, numbers[0]) == result) {
            return true;
        }
        return false;
    }
    long long new_var = numbers[0];
    vector<int> new_numbers(numbers.begin() + 1, numbers.end());
    if (var * new_var <= result) {
        if (findEquation_2(result, new_numbers, var * new_var)) {
            return true;
        }
    }
    if (var + new_var <= result) {
        if (findEquation_2(result, new_numbers, var + new_var)) {
            return true;
        }
    }
    if (concatenate(var, new_var) <= result) {
        if (findEquation_2(result, new_numbers, concatenate(var, new_var))) {
            return true;
        }
    }
    return false;
}

bool isTrueEquation(long long result, vector<int> numbers) {
    long long var = numbers[0];
    numbers.erase(numbers.begin());
    if (numbers.empty()) {
        return var == result;
    }
    return findEquation(result, numbers, var);
}

bool isTrueEquation_2(long long result, vector<int> numbers) {
    long long var = numbers[0];
    numbers.erase(numbers.begin());
    if (numbers.empty()) {
        return var == result;
    }
    return findEquation_2(result, numbers, var);
}

int main() {
    ifstream input("07.txt");
    string line;
    vector<tuple<long long, vector<int>>> operators;

    while (getline(input, line)) {
        long long result = stoll(line.substr(0, line.find(':')));
        int pos = line.find(' ')+1;
        vector<int> values;

        while (line.find(' ', pos) < line.find('\0', pos)) {
            values.push_back(stoi(line.substr(pos, line.find(' ', pos))));
            pos = line.find(' ', pos)+1;
        }
        values.push_back(stoi(line.substr(pos, line.size())));

        operators.push_back(make_tuple(result, values));
    }
    unsigned long long calibration_result = 0;
    unsigned long long second_calibration_result = 0;

    int i = 0;
    for (tuple<long long, vector<int>> op : operators) {
        if (isTrueEquation(get<0>(op), get<1>(op))) {
            calibration_result += get<0>(op);
        }
        if (isTrueEquation_2(get<0>(op), get<1>(op))) {
            second_calibration_result += get<0>(op);
        }
        i++;
        cout << i << "\n";
    }

    cout << "Part 1 : Total calibration result : " << calibration_result << "\n";
    cout << "Part 2 : Total calibration result : " << second_calibration_result;

    return 0;
}
