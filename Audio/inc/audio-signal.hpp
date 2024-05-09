#ifndef AUDIO_STATION_AUDIO_SIGNAL_HPP
#define AUDIO_STATION_AUDIO_SIGNAL_HPP

#include "audio-waveform.hpp"

namespace audiostation {

    struct AudioSignal {
        audiostation::Waveform waveform;
        double frequency;
        double amplitude;
        double phase;
    };
}

#endif // AUDIO_STATION_AUDIO_SIGNAL_HPP
