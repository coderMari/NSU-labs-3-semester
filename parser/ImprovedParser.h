#pragma warning( disable : 4101 )
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <stdexcept>


template <typename... Types>
class ImprovedParser {
public:
    ImprovedParser(std::istream& file, int skip = 0, char delimiter = ',', char quotechar = '"')
        : file(file), delimiter(delimiter), quotechar(quotechar) {

        std::string line;
        while (skip != 0) {
            std::getline(file, line);
            skip--;
        }

        fileSize = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
        
        file.seekg(0, std::ios::beg);
    }

    template <typename... FieldTypes, size_t... Is>
    std::tuple<FieldTypes...> processLine(std::istream& ss, std::index_sequence<Is...>) {
        return { readField<FieldTypes, Is>(ss)... };
    }

    template <typename FieldType, size_t I>
    FieldType readField(std::istream& ss) {
        if constexpr (std::is_same_v<FieldType, int>) {
            try {
                std::string field;
                std::getline(ss, field, delimiter);
                return std::stoi(field);
            }
            catch (const std::invalid_argument& e) {
                return 0;
            }
        }
        else if constexpr (std::is_same_v<FieldType, float>) {
            try {
                std::string field;
                std::getline(ss, field, delimiter);
                return std::stof(field);
            }
            catch (const std::invalid_argument& e) {
                return 0;
            }
        }
        else {
            std::string field;
            char nextChar;
            while (ss.get(nextChar)) {
                if (nextChar == quotechar) {
                    std::getline(ss, std::get<I>(fieldBuffer), quotechar);
                    break;
                }
                else {
                    field += nextChar;
                }
            }

            if constexpr (I < sizeof...(Types) - 1) {
                ss.ignore(delimiter);
            }

            return std::get<I>(fieldBuffer) + field;
        }
    }

    class iterator {
    public:
        iterator(ImprovedParser& parser, size_t index) : parser(parser), index(index) {
            ++(*this);
        }

        iterator& operator++() {
            if (std::getline(parser.file, currentLine)) {
                std::stringstream ss(currentLine);
                currentTuple = parser.processLine<Types...>(ss, std::index_sequence_for<Types...>{});
            }
            else {
                index = parser.file.eof() ? parser.fileSize : parser.fileSize + 1;
            }
            ++index;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return index != other.index;
        }

        std::tuple<Types...> operator*() const {
            return currentTuple;
        }

    private:
        ImprovedParser& parser;
        size_t index = 0;
        std::string currentLine;
        std::tuple<Types...> currentTuple;
    };

    iterator begin() {
        file.seekg(0, std::ios::beg);
        return iterator(*this, 0);
    }

    iterator end() {
        return iterator(*this, fileSize);
    }

private:
    std::istream& file;
    char delimiter;
    char quotechar;
    size_t fileSize = 0;
    std::tuple<typename std::decay<Types>::type...> fieldBuffer;
};