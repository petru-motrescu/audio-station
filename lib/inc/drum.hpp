#ifndef AUDIO_STATION_DRUM_HPP
#define AUDIO_STATION_DRUM_HPP

#include <memory>
#include "audio-sample.hpp"
#include "envelope.hpp"
#include "instrument.hpp"
#include "note.hpp"
#include "oscillator.hpp"

namespace audiostation {

    struct DrumSignal {
        Wave wave = Wave::Sine;
        double frequency = Frequency::C4;
        double amplitude = 0.5;
    };

    struct DrumConfig {
        DrumSignal opening_signal = {
            .wave = Wave::Triangle, 
            .frequency = Frequency::A2, 
            .amplitude = 0.5
        };

        DrumSignal closing_signal = { 
            .wave = Wave::Sine, 
            .frequency = Frequency::B0, 
            .amplitude = 1.0
        };

        unsigned attack_duration = 0;
        unsigned sustain_duration = 0;
        unsigned release_duration = 200;

        // TODO Ratio
    };

    struct DrumImpl;

    class Drum : public Instrument {
    public:
        Drum();
        Drum(DrumConfig config);
        ~Drum();
        
        void trigger(Note note = Note::C4) override;
        void release(Note note = Note::C4) override { };
        AudioSample render() override;

    private:
        std::unique_ptr<DrumImpl> impl;
    };
}

#endif // AUDIO_STATION_DRUM_HPP
