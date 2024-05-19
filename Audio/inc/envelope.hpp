#ifndef AUDIO_STATION_ENVELOPE_HPP
#define AUDIO_STATION_ENVELOPE_HPP

#include "config.hpp"

namespace audiostation {

    struct Envelope {
        unsigned atack_millis;
        unsigned decay_millis;
        double sustain_level; // 0.0 <= sustain_level <= 1.0
        unsigned release_millis;
    };

    struct RenderableEnvelope {
        double atack_ticks;
        double decay_ticks;
        double sustain_level;
        double release_ticks;
    };

    struct Envelopes {
        static inline RenderableEnvelope to_renderable_envelope(Envelope& envelope) {
            return {
                .atack_ticks = envelope.atack_millis * Config::SAMPLE_RATE / 1000.0,
                .decay_ticks = envelope.decay_millis * Config::SAMPLE_RATE / 1000.0,
                .sustain_level = envelope.sustain_level,
                .release_ticks = envelope.release_millis * Config::SAMPLE_RATE / 1000.0,
            };
        }
    };
}

#endif // AUDIO_STATION_ENVELOPE_HPP
