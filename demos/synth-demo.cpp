#include "audio-station.hpp"
#include "synth.hpp"
#include "utils.hpp"
using namespace audiostation;

void synth_demo() {    
    Synth synth({
        .wave = Wave::Triangle,
        .amplitude = 0.4,
        .harmonics = 7,
        .envelope = {
            .attack_duration = 10,
            .decay_duration = 20,
            .sustain_level = 1.0,
            .release_duration = 1000,
        }
    });

    AudioStation station;
    station.init();
    station.play(&synth);

    std::vector<Note> notes = { 
        Note::C4, Note::F4, Note::A4, Note::D5,
        Note::B4, Note::A4, Note::F4, Note::C4,
    };

    for (auto note : notes) {
        synth.trigger(note);
        sleep_for_millis(200);
        synth.release(note);
    }

    sleep_for_seconds(2);
    station.stop();
}
