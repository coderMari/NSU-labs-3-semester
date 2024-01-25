#pragma once
#include <iostream>

#include "converter.h"
#include "exeption.h"

class ConvertFactory {

public:

    Converter* createConverter(std::vector<std::string> param) {
        if (param[0] == "mute") {

            return new MuteConverter(param);
        }
        else if (param[0] == "mix") {

            return new MixerConverter(param);
        }
        else if (param[0] == "add"){

            return new AddVolumeConverter(param);
        }

        else {

            throw SoundProcessorException("wrong config");
        }
    }
};