#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Field;

#include "field.h"



class Console {

public:
	
	std:: string in_filename;
	std::string out_filename;
	int iter;
	int size_v;
	int size_h;

	Console(int argc, char** argv);

	Console(const Console& b);

	std::vector<int> Console::get_size();

	void out();

	void process();
};

