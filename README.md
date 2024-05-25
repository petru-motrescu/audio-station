# Audio Station

A toy digital audio station for Mac.

The project consists of two parts:
- a library for generating and playing sounds
- a DAW-like app that uses the library (coming soon)


### The audio library

Built on top of Core Audio, the audio library can generate audio signals and play them in real-time. For better or for worse the library has been implemented in C++. There is a C api available as well so that it can be easily used from any Swift of Objective-C app on Mac.

You can even try the library directly from terminal. Here is an example of doing so:
```cpp
void run_track_demo() {
    AudioStation station;
    station.init();

    BassDrum kick({
        .waveform = Waveform::Sine,
        .atack_frequency = 120,
        .decay_frequency = 30,
        .decay_millis = 150,
        .amplitude = 0.5,
    });

    BassDrum click({
        .waveform = Waveform::Sine,
        .atack_frequency = 2000,
        .decay_frequency = 2000,
        .decay_millis = 100,
        .amplitude = 0.2,
    });

    Synth bass({
        .waveform = Waveform::Triangle,
        .amplitude = 0.6,
        .envelope = {
            .atack_millis = 5, 
            .decay_millis = 20, 
            .sustain_level = 0.9, 
            .release_millis = 500
        }
    });

    auto ticks = Config::SAMPLE_RATE / 8;

    std::vector<TrackNote> kick_notes = {
        { .start_tick =  0 * ticks },
        { .start_tick =  4 * ticks },
        { .start_tick =  8 * ticks },
        { .start_tick = 12 * ticks },
    };

    std::vector<TrackNote> click_notes = {
        { .start_tick = ( 0 + 2) * ticks },
        { .start_tick = ( 4 + 2) * ticks },
        { .start_tick = ( 8 + 2) * ticks },
        { .start_tick = (12 + 2) * ticks },
    };

    std::vector<TrackNote> bass_notes_1 = {
        { .note = Note::E1, .start_tick =  0 * ticks },
        { .note = Note::E1, .start_tick =  4 * ticks },
        { .note = Note::E1, .start_tick =  8 * ticks },
        { .note = Note::G1, .start_tick = 12 * ticks },
    };

    std::vector<TrackNote> bass_notes_2 = {
        { .note = Note::B1, .start_tick =  0 * ticks },
        { .note = Note::A1, .start_tick =  4 * ticks },
        { .note = Note::G1, .start_tick =  8 * ticks },
        { .note = Note::E1, .start_tick = 12 * ticks },
    };

    TrackLane kick_lane = {
        .label = "Kick",
        .instrument = &kick,
        .bars = {
            { .offset =  0 * ticks, .notes = kick_notes },
            { .offset = 16 * ticks, .notes = kick_notes },
            { .offset = 32 * ticks, .notes = kick_notes },
            { .offset = 48 * ticks, .notes = kick_notes },
        }
    };

    TrackLane click_lane = {
        .label = "Click",
        .instrument = &click,
        .bars = {
            { .offset =  0 * ticks, .notes = click_notes },
            { .offset = 16 * ticks, .notes = click_notes },
            { .offset = 32 * ticks, .notes = click_notes },
            { .offset = 48 * ticks, .notes = click_notes },
        }
    };

    TrackLane bass_lane = {
        .label = "Bass",
        .instrument = &bass,
        .bars = {
            { .offset =  0 * ticks, .notes = bass_notes_1 },
            { .offset = 16 * ticks, .notes = bass_notes_1 },
            { .offset = 32 * ticks, .notes = bass_notes_1 },
            { .offset = 48 * ticks, .notes = bass_notes_2 },
        }
    };

    Track track { 
        .lanes = { &kick_lane, &click_lane, &bass_lane },
        .debug = true,
    };

    station.play(&track);
    sleep(9000);

    station.stop();
}
```

To run the above example:
```bash
cd Audio
make build
make run
```


### The app

<img src="screenshot.png" width="800"/>

The app uses SceneKit for the graphics and the audio library to play some silly sounds. Very much a work in progress.


### Documentation

- [DAW, by Wikipedia](https://en.wikipedia.org/wiki/Digital_audio_workstation)
- [Waveform, by Wikipedia](https://en.wikipedia.org/wiki/Waveform)
- [Waveforms, by Josh Comeau](https://pudding.cool/2018/02/waveforms/)
- [Envelope, by Wikipedia](https://en.wikipedia.org/wiki/Envelope_(music))
- [Piano key frequencies, by Wikipedia](https://en.wikipedia.org/wiki/Piano_key_frequencies)
- [Drum kit, by Wikipedia](https://en.wikipedia.org/wiki/Drum_kit)
- [How To Get the Perfect Kick Drum Sound, by Output Mag](https://output.com/blog/get-perfect-kick-drum)
- [Apple Audio](https://developer.apple.com/audio/)
- [Apple Core Audio](https://developer.apple.com/library/archive/documentation/MusicAudio/Conceptual/CoreAudioOverview)
- [Apple SceneKit](https://developer.apple.com/documentation/scenekit)


### Footnote

_Educational purpose only, no guarantees, no promises. Not connected to my employer._
