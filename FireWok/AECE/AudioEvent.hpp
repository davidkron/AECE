//
// Created by david on 2016-06-25.
//

#ifndef FIREWOK_AUDIOEVENT_HPP
#define FIREWOK_AUDIOEVENT_HPP

#include "AefFile.h"

namespace AECE {

    struct AudioEvent {
        const int InstrumentId;
        const Pattern::Types Kind;
        const int Parameter;

        AudioEvent(int instrumentId, Pattern::Types kind, int parameter = 0);
    };

}

#endif //FIREWOK_AUDIOEVENT_HPP
