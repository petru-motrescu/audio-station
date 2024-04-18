#ifndef AUDIO_STATION_TEST_ASSERTS_HPP
#define AUDIO_STATION_TEST_ASSERTS_HPP

#include <iostream>
#include <string>
#include <cmath>

namespace audiostation {
    void assert_equal(
        double expected, 
        double actual, 
        double epsilon, 
        std::string message
    );
}

#endif // AUDIO_STATION_TEST_ASSERTS_HPP
