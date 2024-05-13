#ifndef AUDIO_STATION_SYNTH_HPP
#define AUDIO_STATION_SYNTH_HPP

#include <memory>
#include "note.hpp"

namespace audiostation {

    struct SynthImpl;

    struct Synth {
        static constexpr Note FIRST_NOTE = Note::A0;
        static constexpr Note LAST_NOTE = Note::C8;

        Synth();
        ~Synth();

        void play_note(Note note);
        void stop_note(Note note);
        bool is_note_live(Note note);

    private:
        std::unique_ptr<SynthImpl> impl;
    };
}

#endif // AUDIO_STATION_SYNTH_HPP
