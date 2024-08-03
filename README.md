# Audio Station

A toy digital audio station for Mac.

The project consists of two parts:
- a library for generating and playing sounds
- a DAW-like app that uses the library (coming soon)


### The audio library

Built on top of Core Audio, the audio library can generate audio signals and play them in real-time. The library is implemented in C++ and it features also a C api so that it can be easily used from any Swift of Objective-C app on Mac.

Here's an example that creates a few instruments and organizes them in a track (see the full version [here](audio-station-lib/test/main.cpp)):
```cpp
void run_song_demo() {
    AudioStation station;
    station.init();

    Drum kick({
        .attack = { .wave = Wave::Triangle, .frequency = Frequency::A2, .amplitude = 0.5 },
        .release = { .wave = Wave::Sine, .frequency = Frequency::B0, .amplitude = 1.0 },
        .duration = 200,
    });

    Drum click({
        .attack = { .wave = Wave::Triangle, .frequency = 2000, .amplitude = 0.2 },
        .release = { .wave = Wave::Sine, .frequency = 2000, .amplitude = 0.1 },
        .duration = 100,
    });

    Noise hihat({ .amplitude = 0.1 });

    Synth bass({
        .wave = Wave::Triangle,
        .amplitude = 0.4,
        .harmonics = 0,
        .envelope = {
            .attack_duration = 5, 
            .decay_duration = 20, 
            .sustain_level = 0.9, 
            .release_duration = 400
        }
    });

    Synth lead({
        .wave = Wave::Sine,
        .amplitude = 0.2,
        .harmonics = 0,
        .envelope = {
            .attack_duration = 5, 
            .decay_duration = 5, 
            .sustain_level = 1.0, 
            .release_duration = 40
        }
    });

    Delay delay({ .time = 80, .level = 0.6, .feedback = 0.75 });
    Reverb reverb;

    Track kick_track = build_kick_track(kick);
    Track click_track = build_click_track(click, delay);
    Track hihat_track = build_hihat_track(hihat);
    Track bass_track = build_bass_track(bass);
    Track lead_track = build_lead_track(lead, reverb);

    Project project({ .tracks = { &kick_track, &click_track, &hihat_track, &bass_track, &lead_track } });

    station.play(&project);
    sleep(9000);

    station.stop();
}
```

To run the above example:
```bash
cd audio-station-lib
make build
make run
```


### The app

<img src="screenshot.png" width="800"/>

The app uses SceneKit for the graphics and the audio library to play some silly sounds. Very much a work in progress.


### References

Articles:
- [Waveforms, by Josh Comeau](https://pudding.cool/2018/02/waveforms/)
- [Oscillators and noise, by Noise Engineering](https://noiseengineering.us/blogs/loquelic-literitas-the-blog/getting-started-oscillators-and-noise)
- [A Generalized Introduction to Modular Analogue Synthesis Concepts, by Kevin Austin](https://econtact.ca/17_4/austin_synthesis.html)
- [How To Get the Perfect Kick Drum Sound, by Output Mag](https://output.com/blog/get-perfect-kick-drum)
- [A bit about reverb, by Nigel Redmon](https://www.earlevel.com/main/1997/01/19/a-bit-about-reverb/)
- [Eurorack 101, by Intellijel](https://intellijel.com/support/eurorack-101/)

Wikipedia:
- [DAW](https://en.wikipedia.org/wiki/Digital_audio_workstation)
- [Wave](https://en.wikipedia.org/wiki/wave)
- [Envelope](https://en.wikipedia.org/wiki/Envelope_(music))
- [Drum kit](https://en.wikipedia.org/wiki/Drum_kit)
- [Delay effect](https://en.wikipedia.org/wiki/Delay_(audio_effect))
- [Reverb effect](https://en.wikipedia.org/wiki/Reverb_effect)
- [Impulse response](https://en.wikipedia.org/wiki/Impulse_response)
- [Piano key frequencies](https://en.wikipedia.org/wiki/Piano_key_frequencies)
- [Harmonic](https://en.wikipedia.org/wiki/Harmonic)

Books:
- [University Physics, by Hugh Young, Roger Freedman, Francis Sears, Mark Zemansky](https://en.wikipedia.org/wiki/University_Physics)
- [Learning Core Audio, by Chris Adamson, Kevin Avila](https://www.oreilly.com/library/view/learning-core-audio/9780321636973/)
- [Physical audio signal processing, by Julius Orion Smith III](https://ccrma.stanford.edu/~jos/pasp/pasp.html)
- [Introduction to digital filters, by Julius Orion Smith III](https://ccrma.stanford.edu/~jos/filters/)

Videos:
- [Modular synths - Become an expert in 10mins, by The Crow Hill Company](https://www.youtube.com/watch?v=umkTjJ-Z6fs)

Apple:
- [Apple Audio](https://developer.apple.com/audio/)
- [Apple Core Audio](https://developer.apple.com/library/archive/documentation/MusicAudio/Conceptual/CoreAudioOverview)
- [Apple SceneKit](https://developer.apple.com/documentation/scenekit)


### Disclaimer

_Educational & fun purpose only, no guarantees, no promises. Not connected to my employer._
