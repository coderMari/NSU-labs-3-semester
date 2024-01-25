#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include "WavIstream.h"

#include "exeption.h"



class WavOstream {

public:

    struct WAVHeader {

        char chunkID[4]; //RIFF
        uint32_t chunkSize; //размер оставшейся части после этого поля
        char format[4]; //формат (WAVE)
        char subchunk1ID[4]; //идентификатор первой подчасти
        uint32_t subchunk1Size; //размер данных в этом подразделе
        uint16_t audioFormat; //формат аудиоданных
        uint16_t numChannels; //кол-во аудиоканалов
        int sampleRate; //частота дискретизации
        uint32_t byteRate; //байтовая скорость
        uint16_t blockAlign; //кол-во байтов для одного сэмпла
        uint16_t bitsPerSample; //кол-во битов для сэмпла
        char subchunk2ID[4]; //идентификатор второй подчасти
        uint32_t subchunk2Size; //размер данных в этой подчасти
    };

    WavOstream(std::string outp, WavIstream &inp) {

        outputFile = outp;
        out.open(outp, std::ios::binary);

        if (!std::filesystem::exists(outp)) {
            throw FileOpenException("Input file not found: " + outp);
        }

        if (!out.is_open()) {
            throw FileOpenException(outp);
        }

        out.write(reinterpret_cast<char*>(&inp.header), sizeof(WAVHeader));

        sampleRate = inp.header.sampleRate;


    }

    void writeSecond(std::vector<short> sec) {

        out.write(reinterpret_cast<const char*>(sec.data()), sampleRate * sizeof(short));
    }

    void writeEmptySecond() {

        std::vector<short> empty(sampleRate, 0);
        out.write(reinterpret_cast<const char*>(empty.data()), sampleRate * sizeof(short));
    }


private:

	std::string outputFile;
	std::ofstream out;
    int sampleRate;
};