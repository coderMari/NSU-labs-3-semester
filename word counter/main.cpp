#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#include "world_counter.h"


int main(int argc, char** argv) {

	
	ifstream in;
	ofstream out;
	in.open(argv[1]);
	out.open(argv[2]);

	if ((!in) || (argc == 0)) {
		cout << "error";
		return 1;
	}
	
	WordCounter counter;
	counter.process(in);
	counter.writeResult(out);

	in.close();
	out.close();
	return 0;
}