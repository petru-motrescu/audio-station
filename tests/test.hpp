#ifndef AUDIO_STATION_TEST_HPP
#define AUDIO_STATION_TEST_HPP

#include "test-runner.hpp"

namespace audiostation {
    inline void test(std::string test_name, const std::function<void()>& test_body) {
        TestRunner::get().run(test_name, test_body);
    };
}

#endif // AUDIO_STATION_TEST_HPP
