//
// Created by david on 2016-06-25.
//

#pragma once


#include "AefFile.h"
#include "typedefs.h"
#include "SongWithAef.h"
#include "AudioEvent.hpp"

namespace AECE {

    struct Precision {
        static const unsigned long long Milli = 10000;
        static const unsigned long long Micro = 1000000;
    };

    typedef std::map<Int64, std::vector<AudioEvent>> RenderedAefEvents;

    class PatternRenderer {

        Int64 _feedbackResolution;
    public:
        PatternRenderer(Int64 feedbackResolution = Precision::Micro) {

        }

        std::map<Int64, std::vector<AudioEvent>> RenderSong(SongWithAef song);

        void RenderPattern(const Pattern &pattern, int instrument, float offset, float timeBetweenHits,
                           Int64 songLength, RenderedAefEvents *Events);

    };

}