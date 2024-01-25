#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


#include "configreader.h"
#include "convertFactory.h"
#include "converter.h"

class Process {

public:
	Process(int argc, char** argv);

	void SoundProc();

private:

	void copyFiles(std::string in, std::ostream& out);

	void swap(std::string* x, std::string* y);

	std::string output;
	std::string conffile;
	std::vector<std::string> files;
	ConfigReader conf;
	ConvertFactory* factory;
};