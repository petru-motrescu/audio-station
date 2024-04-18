#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include "tests.hpp"
using namespace audiostation;

int main() {
    std::cout << "🧪 Running tests" << std::endl;
    test_sine_wave_rendering();
    test_square_wave_rendering();
    std::cout << "✅ All tests done" << std::endl;
    return 0;
}
