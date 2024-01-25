#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

class ConfigReader {

public:

	ConfigReader() {}

	ConfigReader(std::string configfile);

	bool open(const std::string& conffile);

	ConfigReader& operator=(const ConfigReader& other);

	void close();

	std::vector<std::string> get_new_conf();

	bool end();

private:

	std::string configfile;
	std::ifstream config;

};