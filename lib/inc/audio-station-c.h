#ifndef AUDIO_STATION_H
#define AUDIO_STATION_H

#ifdef __cplusplus
extern "C" {
#endif

typedef long AudioStationHandle;
typedef long SynthHandle;

AudioStationHandle audio_station_init();
void audio_station_play(AudioStationHandle audio_station, SynthHandle synth);
void audio_station_dispose(AudioStationHandle audio_station);

SynthHandle synth_init();
void synth_play_note(SynthHandle synth, int note);
void synth_stop_note(SynthHandle synth, int note);
void synth_dispose(SynthHandle synth);

#ifdef __cplusplus
}
#endif

#endif // AUDIO_STATION_H
