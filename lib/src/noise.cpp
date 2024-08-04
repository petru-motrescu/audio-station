#include <iostream>
#include <random>
#include "noise.hpp"
using namespace audiostation;

constexpr double PI_x_2 = 2 * M_PI;

static std::random_device noise_device;
static std::mt19937 noise_generator(noise_device());

struct audiostation::NoiseImpl {
    NoiseConfig config;
    bool is_live;
};

audiostation::Noise::Noise(NoiseConfig config) {
    this->impl = std::make_unique<NoiseImpl>();
    this->impl->config = config;
    this->impl->is_live = false;
}

audiostation::Noise::~Noise() {
    this->impl.reset();
}

void audiostation::Noise::trigger(Note note) {
    this->impl->is_live = true;
}

void audiostation::Noise::release(Note note) {
    this->impl->is_live = false;
}

double audiostation::Noise::render() {
    if (!this->impl->is_live) {
        return 0;
    }

    std::uniform_real_distribution<> distribution(0, PI_x_2);
    return sin(distribution(noise_generator)) * this->impl->config.amplitude;
}
