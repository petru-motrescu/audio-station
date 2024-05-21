#ifndef AUDIO_STATION_SYNTH_HPP
#define AUDIO_STATION_SYNTH_HPP

#include <memory>
#include "envelope.hpp"
#include "instrument.hpp"
#include "note.hpp"
#include "waveform.hpp"

namespace audiostation {

    struct SynthConfig {
        Waveform waveform = Waveform::Triangle;
        double amplitude = 0.5;
        Envelope envelope = {
            .atack_millis = 10,
            .decay_millis = 100,
            .sustain_level = 0.9,
            .release_millis = 1000,
        };
    };

    struct SynthImpl;

    struct Synth : public Instrument {
        Synth();
        Synth(SynthConfig config);
        ~Synth();
        
        void set_envelope(Envelope envelope);

        void play_note(Note note);
        void stop_note(Note note);
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
