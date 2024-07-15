#ifndef AUDIO_STATION_OSCILLATOR_HPP
#define AUDIO_STATION_OSCILLATOR_HPP

#include <memory>
#include "instrument.hpp"
#include "wave.hpp"
#include "frequency.hpp"

namespace audiostation {

    struct OscillatorImpl;

    class Oscillator : public Instrument {
    public:
        Oscillator(
            Wave wave = Wave::Sine,
            double frequency = Frequency::C4,
            double amplitude = 0.5
        );
        ~Oscillator();

        void play(Note note = Note::C4) override;
        void stop(Note note = Note::C4) override;
        double render() override;

    private:
        std::unique_ptr<OscillatorImpl> impl;
    };
}

#endif // AUDIO_STATION_OSCILLATOR_HPP
