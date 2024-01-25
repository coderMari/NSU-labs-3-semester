#include <iostream>
#include <stdexcept>

#include "process.h"
#include "exeption.h"

int main() {

    try {

        int argc = 6;
        char* argv[] = {"./SoundProcessor.exe", "-c", "config.txt", "out.wav", "funkorama.wav", "district_four.wav"};
        Process a(argc, argv);
        a.SoundProc();
    }
    catch (const UnsupportedFormatException& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (const FileOpenException& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
