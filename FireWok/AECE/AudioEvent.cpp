//
// Created by david on 2016-06-25.
//

#include "AudioEvent.hpp"

AECE::AudioEvent::AudioEvent(int instrumentId, Pattern::Types kind, int parameter)
        : InstrumentId(instrumentId), Kind(kind), Parameter(parameter) {
}