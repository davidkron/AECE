//
// Created by david on 2016-06-19.
//

#pragma once

#include <map>
#include "SongWithAef.h"
#include "typedefs.h"
#include "PatternRenderer.hpp"
#include "AudioEvent.hpp"

namespace AECE {

    class Engine {
        std::map<std::string, SongWithAef> _songs;
        std::function<void(std::string)> _musicPlayer;
        std::function<Int64(std::string)> _getSongPos;
        Int64 songLength;
        std::map<Int64, std::vector<AudioEvent>> Events;
        typedef std::map<long long int, std::vector<AECE::AudioEvent>>::iterator songIterator;
        SongWithAef _currentSong;
        songIterator nextPos;
        Int64 _feedbackResolution;
    public:
        Engine(std::vector<SongWithAef> songs,
               std::function<void(std::string)> musicPlayer,
               std::function<Int64(std::string)> getSongPos,
               Int64 feedbackResolution = Precision::Micro);

        void StartPlaying(std::string songName);

        std::vector<AudioEvent> QueryEvents();
    };
}
