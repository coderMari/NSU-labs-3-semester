#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <algorithm>
#include <math.h>


#include "field.h"
#include "console.h"


Field::Field(Console inp) {

	std::ifstream in(inp.in_filename);
	std::string str = "";
	std::getline(in, str);
	if (str != "#Life 1.06") {
		throw "wrong input";
	}
	int x, y;

	this->birth = 0;
	this->survival = 0;
	std::vector<int> mas = inp.get_size();
	this->size_v = mas[0];
	this->size_h = mas[1];

	std::getline(in, str);
	
	this->name = str.substr(3);

	std::getline(in, str);
	this->rule = str;

	int i = 4;
	while (str[i] != '/') {

		this->birth |= 1 << (str[i] - '0');
		i++;
	}
	i++;
	while (i < str.size()) {

		i++;
		this->survival |= 1 << (str[i] - '0');
	}
	
	while (!in.eof()) {

		in >> x;
		in >> y;
		Cell a(x, y);
		this->matrix.insert(a);
	}
	in.close();
}

Field::Field(const Field& b) {

	this->birth = b.birth;
	this->survival = b.survival;
	this->matrix = b.matrix;
	this->size_h = b.size_h;
	this->size_v = this->size_v;
}

void Field::print() {

	

	std::set<Cell> another = this->matrix;

	

	for (int i = 0; i < this->size_v; i++) {
		std::cout << "		" ;
		for (int j = 0; j < this->size_h; j++) {
			if (!another.empty()) {

				Cell a(i, j);
				if (a == *another.begin()) {
					std::cout << (unsigned char)254;
					another.erase(another.begin());
				}
				else {

					std::cout << (unsigned char)95;
				}
			}
			else {

				std::cout << (unsigned char)95;
			}
			
		}
		
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Field::next() {

	std::set <Cell> next_matrix;

	for (auto it : this->matrix) {
		int x = it.get_first();
		int y = it.get_second();
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {

				int r = (x + i + this->size_v) % this->size_v;
				int c = (y + j + this->size_h) % this->size_h;
				Cell a(r, c);
				unsigned char neigs = get_neighs(r, c);
				if (std::any_of(this->matrix.begin(), this->matrix.end(), [&](Cell b)
					{return b == a; })) {

					if (neigs & this->survival) {
						next_matrix.insert(a);
					}
				}
				else {

					if (neigs & this->birth) {
						next_matrix.insert(a);
					}
				}

			}
		}
	}

	this->matrix = next_matrix;
}

std::string Field::get_name() {
	
	return this->name;
}

void Field::out_file(std::ostream& file) {

	for (auto it : this->matrix) {

		file << it.print_place() << std::endl;
	}
}

unsigned char Field::get_neighs(int x, int y) {

	char num = 0;
	std::set <Cell> another = this->matrix;
	for (auto it : this->matrix) {


		int a = abs(it.get_first() - x) ;
		int b = abs(it.get_second() - y);

		if (a > this->size_v / 2) a = this->size_v - a;
		if (b > this->size_h / 2) b = this->size_h - b;

		double distance = sqrt(a * a + b * b);
		
		if (distance < 2 && distance > 0) {

			num++;
		}
	}
	return (1 << num);
}

std::string Field::get_rule() {

	return this->rule;
}

bool operator==(const Cell& a, const Cell& b) {

	if (a.place == b.place) {

		return true;
	}
	return false;
}

bool operator <(const Cell& a, const Cell& b) {

	return (a.get_first() < b.get_first() || ((a.get_first() == b.get_first()) && (a.get_second() < b.get_second())));
}