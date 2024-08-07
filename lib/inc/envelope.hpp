#ifndef AUDIO_STATION_ENVELOPE_HPP
#define AUDIO_STATION_ENVELOPE_HPP

#include <memory>
#include "config.hpp"
#include "control-signal-source.hpp"

namespace audiostation {

    struct EnvelopeConfig {
        unsigned attack_duration = 0;
        unsigned decay_duration = 0;
        double sustain_level = 1.0;
        unsigned release_duration = 0;
        unsigned sample_rate = Config::SAMPLE_RATE;
    };

    struct EnvelopeImpl;

    class Envelope : public ControlSignalSource {
    public:
        Envelope();
        Envelope(EnvelopeConfig config);
        Envelope(const Envelope& other);
        Envelope(Envelope&& other);
        Envelope& operator=(Envelope&& other);
        virtual ~Envelope();

        void trigger();
        void release();
        bool is_live() const;
        ControlSample render() override;
    
    private:
        std::unique_ptr<EnvelopeImpl> impl;
    };
}

#endif // AUDIO_STATION_ENVELOPE_HPP
