#ifndef AUDIO_STATION_BASS_DRUM_HPP
#define AUDIO_STATION_BASS_DRUM_HPP

#include <memory>
#include "envelope.hpp"
#include "instrument.hpp"
#include "note.hpp"
#include "wave.hpp"

namespace audiostation {

    struct BassDrumConfig {
        Wave wave = Wave::Sine;
        double atack_frequency = 180;
        double decay_frequency = 40;
        double decay_millis = 200;
        double amplitude = 0.6;
    };

    struct BassDrumImpl;

    struct BassDrum : public Instrument {
        BassDrum();
        BassDrum(BassDrumConfig config);
        ~BassDrum();
        
        void play();
        void play_note(Note note) override { play(); };
        void stop_note(Note note) override { };
    
    // internal:
        double render() override;

    private:
        std::unique_ptr<BassDrumImpl> impl;
    };
}

#endif // AUDIO_STATION_BASS_DRUM_HPP
