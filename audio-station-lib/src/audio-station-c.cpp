#include <vector>
#include "audio-station-c.h"
#include "audio-station.hpp"
#include "note.hpp"
#include "project.hpp"
#include "synth.hpp"
using namespace audiostation;

AudioStationHandle audio_station_init() {
    auto station = new AudioStation();
    station->init();
    return reinterpret_cast<AudioStationHandle>(station);
}

void audio_station_play(AudioStationHandle audio_station, SynthHandle synth) {
    reinterpret_cast<AudioStation*>(audio_station)->play(reinterpret_cast<Synth*>(synth));
}

void audio_station_dispose(AudioStationHandle audio_station) {
    auto station = reinterpret_cast<AudioStation*>(audio_station);
    station->stop();
    delete station;
}

SynthHandle synth_init() {
    return reinterpret_cast<SynthHandle>(new Synth({
        .harmonics = 15
    }));
}

void synth_play_note(SynthHandle synth, int note) {
    reinterpret_cast<Synth*>(synth)->trigger(Notes::from_int(note));
}

void synth_stop_note(SynthHandle synth, int note) {
    reinterpret_cast<Synth*>(synth)->release(Notes::from_int(note));
}

void synth_dispose(SynthHandle synth) {
    delete reinterpret_cast<Synth*>(synth);
}
