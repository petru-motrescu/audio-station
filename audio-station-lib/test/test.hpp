#ifndef AUDIO_STATION_TEST_HPP
#define AUDIO_STATION_TEST_HPP

#include <exception>
#include <functional>
#include <iostream>
#include <string>

namespace audiostation {

    void test(std::string test_name, const std::function<void()>& test_body) {
        try {
            test_body();
            std::cout << "✅ " << test_name << std::endl;
        }
        catch (const std::exception& ex) {
            std::cout << "❌ " << test_name << " : " << ex.what() << std::endl;
        }
    }
}

#endif // AUDIO_STATION_TEST_HPP
