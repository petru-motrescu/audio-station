#ifndef AUDIO_STATION_INSTRUMENT_HPP
#define AUDIO_STATION_INSTRUMENT_HPP

namespace audiostation {

    struct Instrument {
        virtual double render() = 0;
    };
}

#endif // AUDIO_STATION_INSTRUMENT_HPP
