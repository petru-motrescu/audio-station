#ifndef AUDIO_STATION_ENVELOPE_HPP
#define AUDIO_STATION_ENVELOPE_HPP

#include "config.hpp"

namespace audiostation {

    struct EnvelopeConfig {
        unsigned atack_duration;
        unsigned decay_duration;
        double sustain_level; // 0.0 <= sustain_level <= 1.0
        unsigned release_duration;
    };

    struct RenderableEnvelope {
        double atack_ticks;
        double decay_ticks;
        double sustain_level;
        double release_ticks;
    };

    struct Envelopes {
        static inline RenderableEnvelope to_renderable_envelope(EnvelopeConfig& envelope) {
            return {
                .atack_ticks = envelope.atack_duration * Config::SAMPLE_RATE / 1000.0,
                .decay_ticks = envelope.decay_duration * Config::SAMPLE_RATE / 1000.0,
                .sustain_level = envelope.sustain_level,
                .release_ticks = envelope.release_duration * Config::SAMPLE_RATE / 1000.0,
            };
        }
    };
}

#endif // AUDIO_STATION_ENVELOPE_HPP
