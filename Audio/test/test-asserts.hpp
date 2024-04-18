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
        std::string message)
    {
        if (abs(expected - actual) > epsilon) {
            std::cout 
                << "Expected: " << expected 
                << " Actual: " << actual 
                << " [" << message << "]" 
                << std::endl;
        }
    }
}

#endif // AUDIO_STATION_TEST_ASSERTS_HPP
