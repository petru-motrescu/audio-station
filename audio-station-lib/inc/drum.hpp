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
        double duration = 500;
    };

    struct DrumImpl;

    class Drum : public Instrument {
    public:
        Drum();
        Drum(DrumConfig config);
        ~Drum();
        
        void play(Note note = Note::C4) override;
        void stop(Note note = Note::C4) override { };
        double render() override;

    private:
        std::unique_ptr<DrumImpl> impl;
    };
}

#endif // AUDIO_STATION_DRUM_HPP
