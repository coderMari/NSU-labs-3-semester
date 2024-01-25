#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#include "world_counter.h"

using namespace std;

int WordCounter::separator(char symb) {
	return (!((symb >= 48 && symb <= 57) || (symb >= 65 && symb <= 90) || (symb >= 97 && symb <= 122)));
}

float WordCounter::percent(float all, int num) {
	return num * 100 / all;
}

map <string, int> WordCounter::add(map <string, int> counter, string word) {

	map <string, int> ::iterator it = counter.find(word);
	if (it == counter.end()) {
		counter.insert(make_pair(word, 1));
	}
	else it->second++;

	return counter;
}

void WordCounter::process(istream& in) {

	string line;
	int begin = 0, end = 0;
	string word;
	map <string, int> ::iterator it;

	while (getline(in, line)) {
		begin = 0;
		end = 0;
		for (int i = 0; i < line.size(); i++) {
			if (separator(line[i])) {
				if (end - begin != 0) {
					sum++;
					word = line.substr(begin, end - begin);
					count = add(count, word);
					begin = end + 1;
					end++;
				}
				else {
					begin++;
					end++;
				}

			}
			else end++;

		}
		if (end - begin != 0) {
			sum++;
			word = line.substr(begin, end - begin);
			count = add(count, word);
		}
	}
}

void WordCounter::writeResult(ostream& out) {

	vector< pair<string, int> > vec;
	copy(count.begin(), count.end(), back_inserter<vector <pair<string, int>>>(vec));
	sort(vec.begin(), vec.end(),
		[](const pair<string, int>& l, const pair<string, int>& r) {
			if (l.second != r.second) return l.second > r.second;
			return l.first < r.first;
		});

	for (auto const& pair : vec) {
		out << pair.first << ";" << pair.second << ";" << percent(sum, pair.second) << endl;
	}
}