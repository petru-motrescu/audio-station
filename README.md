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

void noise_demo() {    
    Noise noise({ .amplitude = 0.1 });
    AudioStation station;
    station.init();
    station.play(&noise);
    noise.trigger();
    sleep_for_seconds(2);
    station.stop();
}
```


### Drum

Generates an audio signal that gradually shifts its initial wave shape, frequency, and amplitude properties towards a final state. Can be used to mimic percussion instruments, like the kick drum in the following example.

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


### Sequencer

The sequencer is telling an instrument which notes to play. The position (offset) and duration of the notes are specified in ticks (a tick corresponds to the rendering of a single audio signal frame).

The notes are organized in blocks to help cloning them at different positions.

```cpp
#include "audio-station.hpp"
#include "mixer.hpp"
#include "sequencer.hpp"
#include "synth.hpp"
#include "utils.hpp"
using namespace audiostation;

constexpr unsigned bar = Config::SAMPLE_RATE / 3;
constexpr unsigned half = bar / 2;

void sequencer_demo() {
    std::vector<SequenceNote> notes_1 = { 
        { .note = Note::GA2, .offset = 0 * bar, .length = half },
        { .note = Note::DE3, .offset = 1 * bar, .length = half  },
        { .note = Note::GA2, .offset = 4 * bar, .length = half  },
        { .note = Note::DE3, .offset = 5 * bar, .length = half  },
    };

    std::vector<SequenceNote> notes_2 = { 
        { .note = Note::AB2, .offset = 0 * bar, .length = half  },
        { .note = Note::DE3, .offset = 1 * bar, .length = half  },
        { .note = Note::AB2, .offset = 4 * bar, .length = half  },
        { .note = Note::DE3, .offset = 5 * bar, .length = half  },
    };

    Sequencer sequencer({
        .loop_enabled = true,
        .loop_length = 16 * bar,
        .blocks = {
            { .offset = 0 * 8 * bar, .notes = notes_1 },
            { .offset = 1 * 8 * bar, .notes = notes_2 }
        }
    });

    Synth synth;
    Mixer mixer({ 
        Track({ .sequencer = &sequencer, .instrument = &synth }),
    });

    AudioStation station;
    station.init();
    station.play(&mixer);
    sleep_for_seconds(8);
    station.stop();
}
```


### Delay

An effect which repeats the signal of an instrument after some bigger delay.

```cpp
#include "audio-station.hpp"
#include "delay.hpp"
#include "drum.hpp"
#include "mixer.hpp"
#include "sequencer.hpp"
#include "utils.hpp"
using namespace audiostation;

constexpr unsigned bar = Config::SAMPLE_RATE / 3;

void delay_demo() {
    Sequencer sequencer({
        .loop_enabled = true,
        .loop_length = 8 * bar,
        .blocks = { SequenceBlock() }
    });

    Drum drum;
    
    Delay delay({
        .time = 250,
        .feedback = 0.8,
        .level = 0.75
    });

    Mixer mixer({ 
        Track({ 
            .sequencer = &sequencer, 
            .instrument = &drum,
            .effects = { &delay },
        }),
    });

    AudioStation station;
    station.init();
    station.play(&mixer);
    sleep_for_seconds(8);
    station.stop();
}
```


### Reverb

An effect that simulates audio reverberation.

```cpp
#include "audio-station.hpp"
#include "mixer.hpp"
#include "reverb.hpp"
#include "sequencer.hpp"
#include "synth.hpp"
#include "utils.hpp"
using namespace audiostation;

constexpr unsigned bar = Config::SAMPLE_RATE;

void reverb_demo() {
    Synth synth;
    Reverb reverb({
        .size = 0.65,
        .level = 0.25
    });

    Sequencer sequencer({
        .loop_enabled = true,
        .loop_length = 8 * bar,
        .blocks = { SequenceBlock() }
    });

    Mixer mixer({ 
        Track({ 
            .sequencer = &sequencer, 
            .instrument = &synth, 
            .effects = { &reverb }
        })
    });

    AudioStation station;
    station.init();
    station.play(&mixer);
    sleep_for_seconds(16);
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
