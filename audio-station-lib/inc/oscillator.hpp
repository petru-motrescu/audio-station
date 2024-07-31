#ifndef AUDIO_STATION_OSCILLATOR_HPP
#define AUDIO_STATION_OSCILLATOR_HPP

#include <memory>
#include "config.hpp"
#include "instrument.hpp"
#include "wave.hpp"
#include "frequency.hpp"

namespace audiostation {

    struct OscillatorConfig {
        Wave wave = Wave::Sine;
        double frequency = Frequency::C4;
        double amplitude = 0.5;
        double phase = 0.0;
        unsigned sample_rate = Config::SAMPLE_RATE;
    };

    struct OscillatorImpl;

    class Oscillator : public Instrument {
    public:
        Oscillator(OscillatorConfig config);
        Oscillator(const Oscillator& other);
        Oscillator(Oscillator&& other);
        ~Oscillator();

        void play(Note note = Note::C4) override;
        void stop(Note note = Note::C4) override;
        void set_amplitude(double amplitude);
        void set_frequency(double frequency);
        void set_phase(double phase);
        double get_amplitude() const;
        double get_frequency() const;
        double get_phase() const;
        bool is_live() const;
    
    // internal:
        double render() override;

    private:
        std::unique_ptr<OscillatorImpl> impl;
    };
}

#endif // AUDIO_STATION_OSCILLATOR_HPP
