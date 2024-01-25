#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

#include "exeption.h"

struct WAVHeader {

    char chunkID[4]; //RIFF
    uint32_t chunkSize; //������ ���������� ����� ����� ����� ����
    char format[4]; //������ (WAVE)
    char subchunk1ID[4]; //������������� ������ ��������
    uint32_t subchunk1Size; //������ ������ � ���� ����������
    uint16_t audioFormat; //������ �����������
    uint16_t numChannels; //���-�� ������������
    int sampleRate; //������� �������������
    uint32_t byteRate; //�������� ��������
    uint16_t blockAlign; //���-�� ������ ��� ������ ������
    uint16_t bitsPerSample; //���-�� ����� ��� ������
    char subchunk2ID[4]; //������������� ������ ��������
    uint32_t subchunk2Size; //������ ������ � ���� ��������
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