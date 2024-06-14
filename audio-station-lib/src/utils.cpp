#include "utils.hpp"

void audiostation::require(bool condition, std::string message) {
    if (!condition) {
        std::cout << message << std::endl;
        abort();
    }
}
