#ifndef AUDIO_STATION_TEST_ASSERTS_HPP
#define AUDIO_STATION_TEST_ASSERTS_HPP

#include <iostream>
#include <string>
#include <cmath>

namespace audiostation {
    void assert_true(bool actual, std::string message = "");
    void assert_false(bool actual, std::string message = "");

    void assert_equal(
        double expected, 
        double actual, 
        double epsilon = 0.00000001, 
        std::string message = ""
    );
}

#endif // AUDIO_STATION_TEST_ASSERTS_HPP
