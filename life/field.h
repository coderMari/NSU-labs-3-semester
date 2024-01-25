#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <set>
#include <algorithm>
#include <set>

#include "cell.h"

class Console;

class Field {

public:

	Field(Console inp);

	Field(const Field& b);

	void print();

	void next();

	std::string get_name();

	void out_file(std::ostream& file);

	std::string get_rule();

private:

	unsigned char get_neighs(int x, int y);
	std::string name;
	std::string rule;
	int size_v;
	int size_h;
	char birth;
	char survival;
	std::set<Cell> matrix;
};