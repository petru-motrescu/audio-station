#include <vector>
#include "audio-station-c.h"
#include "audio-station.hpp"
#include "note.hpp"
#include "synth.hpp"
#include "track.hpp"
using namespace audiostation;

AudioStationHandle audio_station_init() {
    auto station = new AudioStation();
    station->init();
    return reinterpret_cast<AudioStationHandle>(station);
}

void audio_station_play(AudioStationHandle handle, TrackHandle track) {
    reinterpret_cast<AudioStation*>(handle)->play(reinterpret_cast<Track*>(track));
}

void audio_station_dispose(AudioStationHandle handle) {
    auto station = reinterpret_cast<AudioStation*>(handle);
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

TrackHandle track_init() {
    return reinterpret_cast<TrackHandle>(new Track());
}

void track_add_synth(TrackHandle track, SynthHandle synth) {
    reinterpret_cast<Track*>(track)->add_live_instrument(reinterpret_cast<Synth*>(synth));
}

void track_dispose(TrackHandle track) {
    delete reinterpret_cast<Track*>(track);
}
