#ifndef AUDIO_STATION_DRUM_HPP
#define AUDIO_STATION_DRUM_HPP

#include <memory>
#include "envelope.hpp"
#include "instrument.hpp"
#include "note.hpp"
#include "wave.hpp"

namespace audiostation {

    struct DrumSignal {
        Wave wave = Wave::Sine;
        double frequency = 180;
        double amplitude = 0.5;
    };

    struct DrumConfig {
        DrumSignal attack;
        DrumSignal release;
        double duration_ms = 500;
    };

    struct DrumImpl;

    struct Drum : public Instrument {
        Drum();
        Drum(DrumConfig config);
        ~Drum();
        
        void play();
        void play_note(Note note) override { play(); };
        void stop_note(Note note) override { };
    
    // internal:
        double render() override;

    private:
        std::unique_ptr<DrumImpl> impl;
    };
}

#endif // AUDIO_STATION_DRUM_HPP
