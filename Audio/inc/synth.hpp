#ifndef AUDIO_STATION_SYNTH_HPP
#define AUDIO_STATION_SYNTH_HPP

#include <memory>
#include "envelope.hpp"
#include "note.hpp"

namespace audiostation {

    struct SynthImpl;

    struct Synth {
        Synth();
        ~Synth();
        
        void set_envelope(Envelope envelope);

        void play_note(Note note);
        void stop_note(Note note);
        bool is_note_live(Note note);
    
    // internal:
        double render();

    private:
        std::unique_ptr<SynthImpl> impl;
    };
}

#endif // AUDIO_STATION_SYNTH_HPP
