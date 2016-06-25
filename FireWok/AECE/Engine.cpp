//
// Created by david on 2016-06-19.
//

#include "Engine.hpp"

using namespace AECE;
using namespace std;

void AECE::Engine::StartPlaying(string songName) {
    PatternRenderer renderer(_feedbackResolution);
    _currentSong = _songs[songName];
    _musicPlayer(_currentSong.Name);
    Events = renderer.RenderSong(_currentSong);
    nextPos = Events.begin();
}

std::vector<AudioEvent> AECE::Engine::QueryEvents() {
    vector<AudioEvent> events;
    auto newPos = _getSongPos(_currentSong.Name);

    if (nextPos == Events.end())
        return events;

    while (nextPos->first <= newPos) {
        for (auto x : nextPos->second)
            events.push_back(x);
        nextPos++;
    }
    return events;
}

AECE::Engine::Engine(vector<SongWithAef> songs,
                     function<void(std::string)> musicPlayer,
                     function<Int64(std::string)> getSongPos,
                     Int64 feedbackResolution) : _musicPlayer(musicPlayer),
                                                 _getSongPos(getSongPos),
                                                 _feedbackResolution(feedbackResolution) {
    for (auto x : songs) {
        _songs.insert(make_pair(x.Name, x));
    }
}