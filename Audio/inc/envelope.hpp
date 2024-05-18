#ifndef AUDIO_STATION_ENVELOPE_HPP
#define AUDIO_STATION_ENVELOPE_HPP

namespace audiostation {

    struct Envelope {
        double atack;
        double decay;
        double sustain;
        double release;
    };
}

#endif // AUDIO_STATION_ENVELOPE_HPP
