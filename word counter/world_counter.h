#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class WordCounter {
private:

	map <string, int> count;

	float sum = 0;

	int separator(char symb);

	float percent(float all, int num);

	map <string, int> add(map <string, int> counter, string word);

public:

	void process(istream& in);

	void writeResult(ostream& out);

};