#include "converter.h"
#include "WavIstream.h"
#include "WavOstream.h"

std::vector<short> sum(std::vector<short> first, std::vector<short> second) {

	for (int i = 0; i < first.size(); i++) {

		if (!second.empty()) {

			first[i] = (first[i] / 2 + second[i] / 2);
		}
		else return first;
	}

	return first;
}

std::vector<short> mul(std::vector<short> sam, short vol) {

	std::vector<int> mas(sam.size());
	for (int i = 0; i < sam.size(); i++) {

		mas[i] = sam[i]*vol;
		sam[i] = (short)mas[i];
	}
	return sam;
}

void  MuteConverter::process(std::vector<std::string> param, std::string inp, std::string outp, std::vector<std::string> files) {
	
	WavIstream first(inp);
	WavOstream second(outp, first);

	int currentSec = 0;

	while (currentSec < start) {

		second.writeSecond(first.getSecond());
		currentSec++;
	}


	while (currentSec >= start && currentSec <= end) {

		second.writeEmptySecond();
		currentSec++;
	}

	while (!first.isEnd()) {

		second.writeSecond(first.getSecond());
	}
}

void MixerConverter::process(std::vector<std::string> param, std::string inp, std::string outp, std::vector<std::string> files) {

	

	WavIstream old1(inp);
	WavIstream old2(files[std::stoi(param[1].substr(1)) - 1]);

	WavOstream out(outp, old1);

	int currentSec = 0;

	while (currentSec < start) {

		out.writeSecond(old1.getSecond());
		currentSec++;
	}

	while (!old1.isEnd()) {

		std::vector<short> sec1 = old1.getSecond();
		if (!old2.isEnd()) {

			std::vector<short> sec2 = old2.getSecond();

			out.writeSecond(sum(sec1, sec2));
		}
		else {

			while (!old1.isEnd()) {

				out.writeSecond(old1.getSecond());
			}
		}
	}
}

void  AddVolumeConverter::process(std::vector<std::string> param, std::string inp, std::string outp, std::vector<std::string> files) {

	WavIstream first(inp);
	WavOstream second(outp, first);


	int currentSec = 0;

	while (currentSec < start) {

		second.writeSecond(first.getSecond());
		currentSec++;
	}

	while (currentSec >= start && currentSec <= end) {

		std::vector<short> sec = first.getSecond();
		second.writeSecond(mul(sec, vol));
		currentSec++;
	}

	while (!first.isEnd()) {

		second.writeSecond(first.getSecond());
	}
}