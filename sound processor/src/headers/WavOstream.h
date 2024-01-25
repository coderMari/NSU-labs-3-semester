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