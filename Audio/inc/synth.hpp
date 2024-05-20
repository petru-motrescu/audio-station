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
        double amplitude = 0.2;
        Envelope envelope = {
            .atack_millis = 10,
            .decay_millis = 100,
            .sustain_level = 0.1,
            .release_millis = 200,
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

    private:
        std::unique_ptr<SynthImpl> impl;
    };
}

#endif // AUDIO_STATION_SYNTH_HPP
