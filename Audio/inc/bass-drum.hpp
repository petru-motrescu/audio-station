#ifndef AUDIO_STATION_BASS_DRUM_HPP
#define AUDIO_STATION_BASS_DRUM_HPP

#include <memory>
#include "envelope.hpp"
#include "instrument.hpp"
#include "note.hpp"
#include "waveform.hpp"

namespace audiostation {

    struct BassDrumImpl;

    struct BassConfig {
        Waveform waveform = Waveform::Sine;
        double atack_frequency = 180;
        double decay_frequency = 40;
        double decay_millis = 200;
        double amplitude = 0.6;
    };

    struct BassDrum : public Instrument {
        BassDrum();
        BassDrum(BassConfig config);
        ~BassDrum();
        
        void play();
    
    // internal:
        double render() override;

    private:
        std::unique_ptr<BassDrumImpl> impl;
    };
}

#endif // AUDIO_STATION_BASS_DRUM_HPP
