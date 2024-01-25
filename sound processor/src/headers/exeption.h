#pragma once

#include <stdexcept>
#include <iostream>

class SoundProcessorException : public std::runtime_error {
public:
    explicit SoundProcessorException(const std::string& message) : std::runtime_error(message) {}
};

class UnsupportedFormatException : public SoundProcessorException {
public:
    explicit UnsupportedFormatException(const std::string& message) : SoundProcessorException(message) {}
};

class FileOpenException : public SoundProcessorException {
public:
    explicit FileOpenException(const std::string& filename) : SoundProcessorException("Error opening file: " + filename) {}
};
