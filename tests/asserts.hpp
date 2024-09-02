#ifndef AUDIO_STATION_TEST_ASSERTS_HPP
#define AUDIO_STATION_TEST_ASSERTS_HPP

#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace audiostation {
    
    void assert_true(bool actual, std::string message = "");
    void assert_false(bool actual, std::string message = "");

    void assert_equal(
        double expected, 
        double actual, 
        std::string message = ""
    );

    void assert_equal(
        double expected, 
        double actual, 
        double epsilon, 
        std::string message = ""
    );

    void assert_equal(
        std::vector<double> expected, 
        std::vector<double> actual, 
        double epsilon = 0.00000001
    );

    template <typename T> void assert_equal(
        std::vector<T> expected, 
        std::vector<T> actual
    ) {
        if (actual != expected) {
            throw std::runtime_error("Vectors are different");
        }
    }
}

#endif // AUDIO_STATION_TEST_ASSERTS_HPP
