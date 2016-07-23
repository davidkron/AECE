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

namespace YAML {
    template<>
    struct convert<AECE::AudioEvent> {
        static Node encode(AECE::AudioEvent &rhs) {
            Node n;
            n["Id"] = rhs.InstrumentId;
            n["Kind"] = rhs.Kind;
            n["Parameter"] = rhs.Parameter;
        }
    };
}

#endif //FIREWOK_AUDIOEVENT_HPP
