#include <iostream>
#include "test-suite.hpp"
using namespace audiostation;

void audiostation::TestSuite::run_tests() {
    std::cout << "🧪 Running tests" << std::endl;
    this->passed_tests = 0;
    this->failed_tests = 0;
    
    run_delay_tests();
    run_oscillator_tests();
    run_synth_tests();
    run_track_tests();
    run_renderer_tests();

    if (this->failed_tests > 0) {
        std::cout << "😬 Some tests failed!" << std::endl;
    } else {
        std::cout << "💪 All tests passed!" << std::endl;
    }
}

void audiostation::TestSuite::test(std::string test_name, const std::function<void()>& test_body) {
    try {
        test_body();
        this->passed_tests++;
        std::cout << "✅ " << test_name << std::endl;
    }
    catch (const std::exception& ex) {
        this->failed_tests++;
        std::cout << "❌ " << test_name << " : " << ex.what() << std::endl;
    }
}
