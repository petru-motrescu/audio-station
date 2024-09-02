#include <algorithm>
#include <iomanip>
#include <sstream>
#include <vector>
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
        std::stringstream str;
        str << "Expected: true, Actual: false "; 
        if (message.size() > 0) {
            str << ", Hint: " << message;
        }
        throw std::runtime_error(str.str());
    }
}

void audiostation::assert_false(bool actual, std::string message) {
    if (actual) {
        std::stringstream str;
        str << "Expected: false, Actual: true "; 
        if (message.size() > 0) {
            str << ", Hint: " << message;
        }
        throw std::runtime_error(str.str());
    }
}

void audiostation::assert_equal(
    double expected, 
    double actual, 
    std::string message)
{
    assert_equal(
        expected, 
        actual, 
        0.00000001, 
        message);
}

void audiostation::assert_equal(
    double expected, 
    double actual, 
    double epsilon, 
    std::string message)
{
    if (fabs(expected - actual) > epsilon) {
        std::stringstream str;
        str << std::setprecision (16) 
            << "Expected: " << expected 
            << ", Actual: " << actual;
        if (message.size() > 0) {
            str << ", Hint: " << message;
        }
        throw std::runtime_error(str.str());
    }
}

void audiostation::assert_equal(
    std::vector<double> expected, 
    std::vector<double> actual, 
    double epsilon)
{
    if (!are_equal(expected, actual, epsilon)) {
        std::stringstream str;
        str << "Expected: ";
        for (auto& x : expected) { str << x << ", "; }
        str << "Actual: ";
        for (auto& x : actual) { str << x << ", "; }
    }
}

