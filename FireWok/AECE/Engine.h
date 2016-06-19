//
// Created by david on 2016-06-19.
//

#pragma once

#include <map>
#include <gsl/span.h>
#include "SongWithAef.h"

namespace AECE{
    class Engine {
        std::map<std::string,SongWithAef> _songs;
        std::function<void(std::string)> _musicPlayer;
        std::function<void(long)> _getSongPos;
    public:
        Engine(gsl::span<SongWithAef> songs,std::function<std::string(void)> musicPlayer,std::function<long(void)> getSongPos) :
                _musicPlayer(musicPlayer), _getSongPos(getSongPos)
        {
            for (auto const & x : songs) { _songs[x.Name] = x; }
        }

        void StartPlaying(std::string songName)
        {
            auto song = _songs[songName];
            _musicPlayer(song.Name);
            auto bps = 60.0f / song.Aef.Tempo;
            auto instrumentId = 0;
            for (auto instrument : song.Aef.Instruments)
            {
                for (auto pattern : instrument.Patterns)
                {
                    auto timeBetweenHits = bps * (4.0f / pattern.HitsPerBar) * 1000;
                    auto offset = pattern.Offset * timeBetweenHits;
                    InitiatePattern(instrumentId, offset, timeBetweenHits, pattern);
                }
                instrumentId++;
            }
        }

        void InitiatePattern(int instrument,float offset,float timeBetweenHits, Pattern pattern)
        {
            auto patternProgression = PatternProgression(pattern, instrument, offset, timeBetweenHits,
            x => _events.Enqueue(x));
            _patternProgessList.Add(patternProgression);
        }

    };
}
