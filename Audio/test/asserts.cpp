#include <iomanip>
#include "asserts.hpp"
using namespace audiostation;

void audiostation::assert_true(bool actual, std::string message) {
    if (!actual) {
        std::cout 
            << "Expected: true, Actual: false " 
            << "[" << message << "]" 
            << std::endl;
    }
}

void audiostation::assert_false(bool actual, std::string message) {
    if (actual) {
        std::cout 
            << "Expected: false, Actual: true " 
            << "[" << message << "]" 
            << std::endl;
    }
}

void audiostation::assert_equal(
    double expected, 
    double actual, 
    double epsilon, 
    std::string message)
{
    if (abs(expected - actual) > epsilon) {
        std::cout 
            << std::setprecision (16)
            << "Expected: " << expected 
            << " Actual: " << actual 
            << " [" << message << "]" 
            << std::endl;
    }
}