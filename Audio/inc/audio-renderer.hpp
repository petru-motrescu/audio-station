#ifndef AUDIO_STATION_AUDIO_RENDERER_HPP
#define AUDIO_STATION_AUDIO_RENDERER_HPP

#include <memory>
#include "oscillator.hpp"
#include "synth.hpp"

namespace audiostation {

    struct AudioRendererImpl;

    struct AudioRenderer {
        AudioRenderer(unsigned sample_rate);
        ~AudioRenderer();

        void add_oscillator(audiostation::Oscillator* oscillator);
        void add_synth(audiostation::Synth* synth);
        double render();

    private:
        std::unique_ptr<AudioRendererImpl> impl;
    };
}

#endif // AUDIO_STATION_AUDIO_RENDERER_HPP
