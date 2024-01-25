#pragma once

class Cell {

public:

	Cell(int x, int y) {

		this->place = std::make_pair(x, y);
	}

	Cell(const Cell& a) {

		this->place = a.place;
	}

	std::pair<int, int> get_place() const{

		return this->place;
	}

	int get_first() const{

		return this->place.first;
	}

	int get_second() const{

		return this->place.second;
	}

	std::string print_place() {

		std::string str = std::to_string(this->place.first);
		str += " ";
		str += std::to_string(this->place.second);

		return str;
	}

	


	std::pair<int, int> place;

};


bool operator==(const Cell& a, const Cell& b);

bool operator <(const Cell& a, const Cell& b);
