#include <iostream>
#include "envelope-renderer.hpp"
using namespace audiostation;

EnvelopedSample audiostation::EnvelopeRenderer::render(
    double sample,
    unsigned ticks_since_live,
    unsigned ticks_at_release,
    RenderableEnvelope& envelope
) {
    double new_sample = sample;
    bool live = true;

    if (ticks_since_live < envelope.atack_ticks) {
        new_sample = sample * ticks_since_live / envelope.atack_ticks;
    } else if (ticks_since_live < (envelope.atack_ticks + envelope.decay_ticks)) {
        auto ticks = ticks_since_live - envelope.atack_ticks;
        auto ratio = ticks / envelope.decay_ticks;
        new_sample = (1 - ratio + ratio * envelope.sustain_level) * sample;
    } else if (ticks_at_release == 0) {
        new_sample = envelope.sustain_level * sample;
    } else if (ticks_since_live < (ticks_at_release + envelope.release_ticks)) {
        auto ticks = ticks_since_live - ticks_at_release;
        new_sample = (1 - ticks / envelope.release_ticks) * envelope.sustain_level * sample;
    } else {
        live = false;
        new_sample = 0;
    }

    return { .sample = new_sample, .live = live };
}
