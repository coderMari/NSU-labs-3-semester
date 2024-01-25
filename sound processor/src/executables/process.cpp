#include <iostream>

#include "process.h"

Process::Process(int argc, char** argv) {

	const std::string conv[] = { "mix\nmix music\nparmetrs:second potok, start\n", "mute\nmute music\nparametrs:start end\n", "add\nadd volume\nparametrs:start, end, power\n" };
	for (int i = 1; i < argc; i++) {


		if (strcmp(argv[i], "-c") == 0) {

			i++;
			this->conffile = argv[i];
			i++;
			this->output = argv[i];
		}
		else if (strcmp(argv[i], "-h") == 0){

			for (int i = 0; i < 3; i++) {

				std::cout << conv[i];
			}
		}
		else {

			this->files.push_back((std::string)argv[i]);
		}
	}

	conf = ConfigReader(conffile);
	factory = new ConvertFactory;
}



void Process::SoundProc() {

	std::ofstream out(this->output, std::ios::binary);

	if (!out.is_open()) {
		throw FileOpenException("out");
	}

	std::string file1 = "out1.wav";
	std::string file2 = "out2.wav";

	std::vector<std::string> parametrs = conf.get_new_conf();
	auto convert = factory->createConverter(parametrs);
	convert->process(parametrs, files[0], file1, files);

	int iterations = 1;

	while (!conf.end()) {

		parametrs = conf.get_new_conf();
		convert = factory->createConverter(parametrs);
		convert->process(parametrs, file1, file2, files);
		swap(&file1, &file2);
		iterations++;
	}

	if (((iterations % 2) == 1) || (iterations == 1)) {

		copyFiles(file1, out);
	}
	else if ((iterations % 2) == 0) {

		copyFiles(file2, out);
	}

	out.close();
}


void Process::copyFiles(std::string in, std::ostream& out) {
	std::ifstream inp(in, std::ios::binary);

	const int bufferSize = 4096;
	char buffer[bufferSize];

	while (inp) {

		inp.read(buffer, bufferSize);
		out.write(buffer, bufferSize);
	}

	inp.close();
}

void Process::swap(std::string* x, std::string* y) {

	std::string z = *x;
	*x = *y;
	*y = z;
}