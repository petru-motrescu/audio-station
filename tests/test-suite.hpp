#ifndef AUDIO_STATION_TEST_SUITE_HPP
#define AUDIO_STATION_TEST_SUITE_HPP

#include <string>
#include <functional>

namespace audiostation {

    struct TestSuite {
    public:
        void run_tests();
    
    private:
        void test(std::string test_name, const std::function<void()>& test_body);
        void run_delay_tests();
        void run_mixer_tests();
        void run_noise_tests();
        void run_oscillator_tests();
        void run_sequencer_tests();
        void run_synth_tests();
    
    private:
        int passed_tests;
        int failed_tests;
    };
}

#endif // AUDIO_STATION_TEST_SUITE_HPP
