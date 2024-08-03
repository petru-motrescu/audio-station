#ifndef AUDIO_STATION_CONTROL_SIGNAL_SOURCE_HPP
#define AUDIO_STATION_CONTROL_SIGNAL_SOURCE_HPP

#include "control-sample.hpp"

namespace audiostation {

    class ControlSignalSource {
    public:
        virtual ControlSample render() = 0;
        virtual ~ControlSignalSource() {};
    };
}

#endif // AUDIO_STATION_CONTROL_SIGNAL_SOURCE_HPP
