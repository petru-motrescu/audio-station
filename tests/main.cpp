#include <iostream>
#include "test-runner.hpp"
#include "test-suite.hpp"
using namespace audiostation;

int main() {
    std::cout << "🧪 Running tests" << std::endl;
    
    delay_tests();
    mixer_tests();
    noise_tests();
    oscillator_tests();
    sequencer_tests();
    synth_tests();

    if (TestRunner::get().get_failed_tests_count() > 0) {
        std::cout << "😬 Some tests failed!" << std::endl;
    } else {
        std::cout << "💪 All tests passed!" << std::endl;
    }

    return 0;
}
