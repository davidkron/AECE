//
// Created by david on 2016-06-19.
//

#pragma once

#include <string>
#include "AefFile.h"


namespace AECE{

    struct SongWithAef {
        const std::string Name;
        std::string Mp3;
        AefFile Aef;

        SongWithAef(std::string mp3, std::string aef, std::string name) :
                Name(name),
                Mp3(mp3),
                Aef(AefFile::FromFile(aef)){}
    };


}