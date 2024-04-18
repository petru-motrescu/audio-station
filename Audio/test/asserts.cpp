#include "asserts.hpp"
using namespace audiostation;

void audiostation::assert_equal(
    double expected, 
    double actual, 
    double epsilon, 
    std::string message)
{
    if (abs(expected - actual) > epsilon) {
        std::cout 
            << "Expected: " << expected 
            << " Actual: " << actual 
            << " [" << message << "]" 
            << std::endl;
    }
}