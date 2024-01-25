#include "configreader.h"

ConfigReader::ConfigReader(std::string configfile) {

	this->configfile = configfile;
	open(configfile);
}

bool ConfigReader::open(const std::string& conffile) {

	config.open(conffile);
	return config.is_open();
}

ConfigReader& ConfigReader::operator=(const ConfigReader& other) {

	if (config.is_open()) {
		config.close();
	}

	this->configfile = configfile;
	config.open(other.configfile);

	return *this;
}

void ConfigReader::close() {
	config.close();
}

std::vector<std::string> ConfigReader::get_new_conf() {
	std::string line;
	std::getline(config, line);

	while (line[0] == '#') {

		std::getline(config, line);
	}

	std::istringstream iss(line);
	std::vector<std::string> words;

	std::string word;
	while (iss >> word) {
		words.push_back(word);
	}

	return words;
}

bool ConfigReader::end() {

	return (config.eof());
}