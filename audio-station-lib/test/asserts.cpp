#include <algorithm>
#include <iomanip>
#include "asserts.hpp"
using namespace audiostation;

bool are_equal(
    double expected, 
    double actual, 
    double epsilon)
{
    return fabs(expected - actual) <= epsilon;
}

bool are_equal(
    std::vector<double> expected, 
    std::vector<double> actual, 
    double epsilon)
{
    if (expected.size() != actual.size()) {
        return false;
    }

    for (int i = 0; i < expected.size(); i++) {
        if (!are_equal(expected[i], actual[i], epsilon)) {
            return false;
        }
    }

    return true;
}

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
    if (fabs(expected - actual) > epsilon) {
        std::cout 
            << std::setprecision (16)
            << "Expected: " << expected 
            << " Actual: " << actual 
            << " [" << message << "]" 
            << std::endl;
    }
}

void audiostation::assert_equal(
    std::vector<double> expected, 
    std::vector<double> actual, 
    double epsilon)
{
    if (!are_equal(expected, actual, epsilon)) {
        std::cout << "Expected: ";
        for (auto& x : expected) { std::cout << x << ", "; }
        std::cout << std::endl << "Actual: ";
        for (auto& x : actual) { std::cout << x << ", "; }
        std::cout << std::endl;
    }
}