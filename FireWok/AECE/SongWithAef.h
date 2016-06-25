//
// Created by david on 2016-06-19.
//

#pragma once

#include <string>
#include "AefFile.h"
#include "typedefs.h"

namespace AECE{

    class SongWithAef {
    public:
        std::string Name;
        std::string Mp3;
        AefFile Aef;
        Int64 Length;

        SongWithAef() { }

        SongWithAef(std::string mp3, std::string aef, std::string name, Int64 length) :
                Name(name),
                Mp3(mp3),
                Length(length),
                Aef(AefFile::FromFile(aef)){}
    };


}