#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

#include "exeption.h"

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

class WavIstream {

public:

    WavIstream(std::string inp) {

        inputFile = inp;
        in.open(inp, std::ios::binary);

        if (!std::filesystem::exists(inp)) {
            throw FileOpenException("Input file not found: " + inp);
        }

        if (!in.is_open()) {
            throw FileOpenException(inp);
        }

        in.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));

    }

    WavIstream(const WavIstream& b) {

        this->in.close();
        this->in.open(b.inputFile, std::ios::binary);
        this->header = b.header;
    }


    std::vector<short> getSecond() {

        std::vector<short> sec(header.sampleRate);
        in.read(reinterpret_cast<char*>(sec.data()), header.sampleRate * sizeof(short));
        sec.resize(in.gcount());
        return sec;
    }

    bool isEnd() {

        return in.eof();
    }

    WAVHeader header;

private:
    std::string inputFile;
    std::ifstream in;
    
};