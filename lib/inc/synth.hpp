#ifndef AUDIO_STATION_SYNTH_HPP
#define AUDIO_STATION_SYNTH_HPP

#include <memory>
#include "audio-sample.hpp"
#include "envelope.hpp"
#include "instrument.hpp"
#include "note.hpp"
#include "wave.hpp"

namespace audiostation {

    struct SynthConfig {
        Wave wave = Wave::Sine;
        double amplitude = 0.5;
        unsigned harmonics = 0;
        EnvelopeConfig envelope = {
            .attack_duration = 10,
            .decay_duration = 20,
            .sustain_level = 0.9,
            .release_duration = 1000,
        };
        unsigned sample_rate = Config::SAMPLE_RATE;
    };

    struct SynthImpl;

    class Synth : public Instrument {
    public:
        Synth();
        Synth(SynthConfig config);
        ~Synth();
        
        void trigger(Note note) override;
        void release(Note note) override;
        bool is_note_live(Note note);
        AudioSample render() override;

    private:
        std::unique_ptr<SynthImpl> impl;
    };
}

#endif // AUDIO_STATION_SYNTH_HPP