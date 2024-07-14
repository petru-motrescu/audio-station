#ifndef AUDIO_STATION_SYNTH_HPP
#define AUDIO_STATION_SYNTH_HPP

#include <memory>
#include "envelope.hpp"
#include "instrument.hpp"
#include "note.hpp"
#include "wave.hpp"

namespace audiostation {

    struct SynthConfig {
        Wave wave = Wave::Triangle;
        double amplitude = 0.5;
        Envelope envelope = {
            .atack_duration = 10,
            .decay_duration = 100,
            .sustain_level = 0.9,
            .release_duration = 1000,
        };
    };

    struct SynthImpl;

    class Synth : public Instrument {
    public:
        Synth();
        Synth(SynthConfig config);
        ~Synth();
        
        void set_envelope(Envelope envelope);
        void play_note(Note note) override;
        void stop_note(Note note) override;
        bool is_note_live(Note note);
    
    // internal:
        double render() override;
        void set_sample_rate(unsigned sample_rate);
        void set_renderable_envelope(RenderableEnvelope envelope);

    private:
        std::unique_ptr<SynthImpl> impl;
    };
}

#endif // AUDIO_STATION_SYNTH_HPP
