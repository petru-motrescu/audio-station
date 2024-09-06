#ifndef AUDIO_STATION_TEST_RUNNER_HPP
#define AUDIO_STATION_TEST_RUNNER_HPP

#include <string>
#include <functional>

namespace audiostation {
    
    struct TestRunner {
    public:
        static TestRunner& get() {
            static TestRunner instance;
            return instance;
        }

        void run(std::string test_name, const std::function<void()>& test_body);
        inline int get_passed_tests_count() const { return passed_tests_count; }
        inline int get_failed_tests_count() const { return failed_tests_count; }
    
    private:
        TestRunner() = default;
        ~TestRunner() = default;
    
    private:
        int passed_tests_count = 0;
        int failed_tests_count = 0;
    };
}

#endif // AUDIO_STATION_TEST_RUNNER_HPP
