#include <iostream>
#include "test-suite.hpp"
using namespace audiostation;

void TestRunner::run(std::string test_name, const std::function<void()>& test_body) {
    try {
        test_body();
        this->passed_tests_count++;
        std::cout << "✅ " << test_name << std::endl;
    }
    catch (const std::exception& ex) {
        this->failed_tests_count++;
        std::cout << "❌ " << test_name << " : " << ex.what() << std::endl;
    }
}
