#ifndef AUDIO_STATION_H
#define AUDIO_STATION_H

#ifdef __cplusplus
extern "C" {
#endif

typedef long AudioStationHandle;
typedef long ProjectHandle;
typedef long SynthHandle;

AudioStationHandle audio_station_init();
void audio_station_play(AudioStationHandle audio_station, ProjectHandle track);
void audio_station_dispose(AudioStationHandle audio_station);

SynthHandle synth_init();
void synth_play_note(SynthHandle synth, int note);
void synth_stop_note(SynthHandle synth, int note);
void synth_dispose(SynthHandle synth);

ProjectHandle project_init();
void project_add_synth(ProjectHandle project, SynthHandle synth);
void project_dispose(ProjectHandle project);

#ifdef __cplusplus
}
#endif

#endif // AUDIO_STATION_H
