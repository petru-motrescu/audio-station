#ifndef AUDIO_STATION_OSCILLATOR_HPP
#define AUDIO_STATION_OSCILLATOR_HPP

#include <memory>
#include "instrument.hpp"
#include "waveform.hpp"
#include "frequency.hpp"

namespace audiostation {

    struct OscillatorImpl;

    struct Oscillator : public Instrument {
        Oscillator(
            Waveform waveform = Waveform::Sine,
            double frequency = Frequency::C4,
            double amplitude = 0.5
        );
        ~Oscillator();

        void play();
        void stop();

    // internal:
        double render() override;

    private:
        std::unique_ptr<OscillatorImpl> impl;
    };
}

#endif // AUDIO_STATION_OSCILLATOR_HPP