//
// Created by david on 2016-06-25.
//

#include "PatternRenderer.hpp"

using namespace AECE;
using namespace std;

map<Int64, vector<AudioEvent>> AECE::PatternRenderer::RenderSong(SongWithAef song) {
    map<Int64, vector<AudioEvent>> Events;
    auto bps = 60.0f / song.Aef.Tempo;
    auto instrumentId = 0;
    for (auto instrument : song.Aef.Instruments) {
        for (auto &pattern : instrument.Patterns) {
            auto timeBetweenHits = bps * (4.0f / pattern.HitsPerBar) * _feedbackResolution;
            auto offset = pattern.Offset * timeBetweenHits;
            RenderPattern(pattern, instrumentId, offset, timeBetweenHits, song.Length, &Events);
        }
        instrumentId++;
    }
    return Events;
}

void AECE::PatternRenderer::RenderPattern(const Pattern &pattern, int instrument, float offset, float timeBetweenHits,
                                          Int64 songLength,
                                          RenderedAefEvents *Events) {
    switch (pattern.Type) {
        case Pattern::Types::IntensityIncrease:
        case Pattern::Types::Hit:
            for (Int64 i = offset; i < songLength; i += timeBetweenHits) {
                Events->at(i).push_back(AudioEvent(instrument, pattern.Type));
            }
        case Pattern::Types::Positional:
            for (Int64 i = offset + pattern.CrotchetTillFirstEvent() * timeBetweenHits; i < songLength;) {
                Events->at(i).push_back(
                        AudioEvent(instrument, pattern.Type,
                                   pattern.As<PositionalPattern>()->GetLocation(i)));
                int timeTillNextEvent = 0;
                i += timeBetweenHits * timeTillNextEvent;
            }
    }
}

