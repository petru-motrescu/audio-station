#include <vector>
#include "audio-station-c.h"
#include "audio-station.hpp"
#include "note.hpp"
using namespace audiostation;

AudioStationHandle audio_station_init() {
    auto station = new AudioStation();
    station->init();
    station->play();
    return reinterpret_cast<AudioStationHandle>(station);
}

void audio_station_dispose(AudioStationHandle handle) {
    auto station = reinterpret_cast<AudioStation*>(handle);
    station->stop();
    delete station;
}

SynthHandle synth_init(AudioStationHandle handle) {
    auto station = reinterpret_cast<AudioStation*>(handle);
    auto synth = new Synth();
    station->add_synth(synth);
    return reinterpret_cast<SynthHandle>(synth);
}

void synth_play_note(SynthHandle handle, int note) {
    auto synth = reinterpret_cast<Synth*>(handle);
    synth->play_note(Notes::from_int(note));
}

void synth_stop_note(SynthHandle handle, int note) {
    auto synth = reinterpret_cast<Synth*>(handle);
    synth->stop_note(Notes::from_int(note));
}

void synth_dispose(SynthHandle handle) {
    auto synth = reinterpret_cast<Synth*>(handle);
    delete synth;
}
