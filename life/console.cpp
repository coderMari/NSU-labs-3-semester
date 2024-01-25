#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <time.h> 

#include "field.h"
#include "console.h"


Console::Console(int argc, char** argv) {

	if (argc % 2 == 0) {

		std::cout <<
			"-f <filename>         Specifies the input file" << std::endl <<
			"- i, --iterations <n>  Specifies the number of iterations(n is an integer)" << std::endl <<
			"- o, --output <filename> Specifies the output file"
			"- s - v, --size - v <n>    Specifies the vertical size(n is an integer)" << std::endl <<
			"- s - h, --size - h <n>    Specifies the horizontal size(n is an integer)" << std::endl <<

			"Usage example : myprogram - f input.txt - i 10 - o output.txt - s - v 5 - s - h 8" << std::endl;
		std::exit(0);
	}

	this->in_filename = "";
	this->out_filename = "";
	this->iter = 0;
	this->size_v = 15;
	this->size_h = 15;
	

	for (int i = 1; i < argc; i++) {
		std::string arg(argv[i]);
		if (arg == "-f") {
			this->in_filename = argv[i + 1];
			i++;
		}
		else if (arg == "-i" || arg == "--iterations") {
			this->iter = std::stoi(argv[i + 1]);
			i++;
		}
		else if (arg == "-o" || arg == "--output") {
			this->out_filename = argv[i + 1];
			i++;
		}
		else if (arg == "-s-v" || arg == "--size-v") {
			this->size_v = std::stoi(argv[i + 1]);
			i++;
		}
		else if (arg == "-s-h" || arg == "--size-h") {
			this->size_h = std::stoi(argv[i + 1]);
			i++;
		}
	}

}

Console::Console(const Console& b) {

	this->in_filename = b.in_filename;
	this->out_filename = b.out_filename;
	this->iter = b.iter;
	this->size_v = b.size_v;
	this->size_h = b.size_h;
}

std::vector<int> Console::get_size() {

	std::vector<int> mas = { this->size_v, this->size_h };
	return mas;
}

void Console::out() {

	if (this->out_filename == "") {

		if (this->in_filename == "") {

			static std::string names[] = { "flying saucer.lif", "glider.lif",  "oscillator.lif" };
			srand((int)time(NULL));
			this->in_filename = names[rand() % 3];

			Field a(*this);

			while (!_kbhit()) {

				system("cls");
				std::cout << "		 " << a.get_name() << std::endl << std::endl;
				a.print();
				a.next();
				Sleep(300);
			}
		}

		else {

			this->iter = 1;
			Field a(*this);
			int tick = 0;

			while (1) {

				std::cout << a.get_name() << std::endl;
				std::cout << a.get_rule() << std::endl;
				std::cout << "tick = " << tick << std::endl;
				a.print();
				std::string userInput;
				std::cout << "Waiting: " << std::endl;
				std::getline(std::cin, userInput);

				std::stringstream ss(userInput);
				std::string word;

				while (ss >> word) {

					if (word == "exit") {

						return;
					}
					else if (word == "dump") {

						ss >> word;
						this->out_filename = word;
						std::ofstream file(this->out_filename);
						file << a.get_name() << std::endl;
						a.out_file(file);
					}
					else if (word == "tick" || word == "t") {

						ss >> word;
						this->iter = std::stoi(word);
						tick += this->iter;
						for (int i = 0; i < this->iter; i++) {

							a.next();
						}
						break;

					}
					else if (userInput == "help") {

						std::cout << "dump <file name> -save the universe to a file\n"
							"tick <n=1> (and abbreviated t <n=1>) - consider n iterations and print the result\n"
							"exit - end the game\n" 
							"help - print a team certificate" << std::endl;
						return;
					}
				}
			}

			
		}
		
	}

	else {

		Field a(*this);

		for (int i = 0; i < this->iter; i++) {

			a.next();
		}
		std::ofstream file(this->out_filename);
		file << a.get_name() << std::endl;
		a.out_file(file);
		file.close();
	}
}
