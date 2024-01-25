#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

class Converter {
public:
    virtual void process(std::vector<std::string> param, std::string inp, std::string outp, std::vector<std::string> files ) = 0;

};

class MuteConverter : public Converter {
public:

	MuteConverter(std::vector<std::string> param) {

		start = std::stoi(param[1]);
		end = std::stoi(param[2]);
	}

	void process(std::vector<std::string> param, std::string inp, std::string outp, std::vector<std::string> files) override;

private:

	int start;
	int end;
};

class MixerConverter : public Converter {
public:

	MixerConverter(std::vector<std::string> param) {

		start = std::stoi(param[2]);
	}

	void process(std::vector<std::string> param, std::string inp, std::string outp, std::vector<std::string> files) override;


private:
	int start;
};

class AddVolumeConverter :public Converter {

public:

	AddVolumeConverter(std::vector<std::string> param) {

		start = std::stoi(param[1]);
		end = std::stoi(param[2]);
		vol = (short)(std::stoi(param[3]));
	}

	void process(std::vector<std::string> param, std::string inp, std::string outp, std::vector<std::string> files) override;

private:

	int start;
	int end;
	short vol;
};