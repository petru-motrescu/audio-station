#ifndef AUDIO_STATION_ENVELOPE_RENDERER_HPP
#define AUDIO_STATION_ENVELOPE_RENDERER_HPP

#include "envelope.hpp"
#include "wave.hpp"

namespace audiostation {

    struct EnvelopedSample {
        double sample;
        bool live;
    };

    class EnvelopeRenderer {
    public:
        static EnvelopedSample render(
            double sample,
            unsigned ticks_since_live,
            unsigned ticks_at_release,
            RenderableEnvelope& envelope
        );
    };
}

#endif // AUDIO_STATION_ENVELOPE_RENDERER_HPP
