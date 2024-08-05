# Audio Station

A toy digital audio workstation for Mac.

### Oscillator

Generates a periodic, oscillating audio signal, in the form of a sine, square or triangle wave.

```cpp
#include "audio-station.hpp"
#include "oscillator.hpp"
#include "utils.hpp"
using namespace audiostation;

void oscillator_demo() {    
    Oscillator oscillator({
        .wave = Wave::Sine,
        .frequency = Frequency::C4,
        .amplitude = 0.25,
    });

    AudioStation station;
    station.init();
    station.play(&oscillator);
    oscillator.trigger();
    sleep_for_seconds(2);
    station.stop();
}
```


### Noise

Generates a continous audio signal, in the form of a random wave.

```cpp
#include "audio-station.hpp"
#include "noise.hpp"
#include "utils.hpp"
using namespace audiostation;
using namespace std::chrono;
using namespace std::this_thread;

void noise_demo() {    
    Noise noise({ .amplitude = 0.25 });
    AudioStation station;
    station.init();
    station.play(&noise);
    noise.trigger();
    sleep_for(seconds(2));   
    station.stop();
}
```


### Drum

Generates an audio signal which gradually changes its shape between 2 states.

```cpp
#include "audio-station.hpp"
#include "drum.hpp"
#include "utils.hpp"
using namespace audiostation;

void drum_demo() {    
    Drum drum({
        .opening_signal = { 
            .wave = Wave::Triangle, 
            .frequency = 120, 
            .amplitude = 0.5
        },
        .closing_signal = { 
            .wave = Wave::Sine, 
            .frequency = 40, 
            .amplitude = 0.6
        },
        .release_duration = 250,
    });

    AudioStation station;
    station.init();
    station.play(&drum);

    for (int i = 0; i < 8; i++) {
        drum.trigger();
        sleep_for_millis(500);
    }
    
    station.stop();
}
```


### Synth

Just like a piano, generates parallel audio signals, one for each triggered note.

```cpp
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
```

### Mixer

A mixer combines the audio signals of multiple instruments, renders effects and drives sequencers.

```cpp
#include "audio-station.hpp"
#include "drum.hpp"
#include "mixer.hpp"
#include "noise.hpp"
#include "utils.hpp"
using namespace audiostation;

void mixer_demo() {
    Drum drum;
    Noise noise;
    Mixer mixer({ 
        Track({ .instrument = &drum }),
        Track({ .instrument = &noise }),
    });

    AudioStation station;
    station.init();
    station.play(&mixer);

    noise.trigger();
    for (int i = 0; i < 8; i++) {
        drum.trigger();
        sleep_for_millis(500);
    }

    station.stop();
}
```

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
