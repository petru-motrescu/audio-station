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

void audio_station_play(AudioStationHandle handle, ProjectHandle project) {
    reinterpret_cast<AudioStation*>(handle)->play(reinterpret_cast<Project*>(project));
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

ProjectHandle project_init() {
    return reinterpret_cast<ProjectHandle>(new Project());
}

void project_add_synth(ProjectHandle project, SynthHandle synth) {
    reinterpret_cast<Project*>(project)->add_live_instrument(reinterpret_cast<Synth*>(synth));
}

void project_dispose(ProjectHandle project) {
    delete reinterpret_cast<Project*>(project);
}
