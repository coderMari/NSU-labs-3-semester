#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <stdexcept>

#include "tuplePrint.h"
#include "ImprovedParser.h"

int main() {

    std::ifstream file("q.csv");

    ImprovedParser<int, std::string> myParser(file, 0, ';', '"');



    for (const auto& row : myParser) {
        std::cout << row << std::endl;
    }

    return 0;

}