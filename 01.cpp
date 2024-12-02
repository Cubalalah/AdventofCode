#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <list>

using namespace std;

int main_01() {
	ifstream input("01.txt");
	string line;
	list<int> locationIDs_1;
	list<int> locationIDs_2;

	while(getline(input, line)){
		string ID_1 = line.substr(0, line.find(" "));
		string ID_2 = line.substr(line.find_last_of(" ")+1, line.size()-line.find_last_of(" ")-1);
		locationIDs_1.push_back(stoi(ID_1));
		locationIDs_2.push_back(stoi(ID_2));
	}
	
	list<int> locationIDs_1_sorted(locationIDs_1);
	list<int> locationIDs_2_sorted(locationIDs_2);

	locationIDs_1_sorted.sort();
	locationIDs_2_sorted.sort();

	int total_distance = 0;

	while (!locationIDs_1_sorted.empty() && !locationIDs_2_sorted.empty()) {
		total_distance += abs(locationIDs_1_sorted.front() - locationIDs_2_sorted.front());
		locationIDs_1_sorted.pop_front();
		locationIDs_2_sorted.pop_front();
	}
	
	cout << "Part 1 - Total distance : " << total_distance << "\n";

	int similarity_score = 0;
	int counter;

	for (int locationID : locationIDs_1) {
		counter = count(locationIDs_2.begin(), locationIDs_2.end(), locationID);
		similarity_score += locationID * counter;
	}

	cout << "Part 2 - Similarity score : " << similarity_score << "\n";

	return 0;
}