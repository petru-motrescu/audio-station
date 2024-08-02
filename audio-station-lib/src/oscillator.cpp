#include <iostream>
#include <iomanip>
#include <utility>
#include "config.hpp"
#include "note.hpp"
#include "frequency.hpp"
#include "oscillator.hpp"
using namespace audiostation;

constexpr double PI_x_2 = 2 * M_PI;
constexpr double HALF_PI = M_PI / 2;
constexpr double HALF_PI_x_0 = 0;
constexpr double HALF_PI_x_1 = HALF_PI;
constexpr double HALF_PI_x_3 = 3 * M_PI / 2;
constexpr double HALF_PI_x_4 = PI_x_2;

static double render_sine_wave(double phase) {
    return sin(phase);
}

static double render_square_wave(double phase) {
    // TODO Calculate without sin() call
    if (sin(phase) < 0) {
        return -1;
    } else {
        return +1;
    }
}

static double render_triangle_wave(double phase) {
    // 0 * PI/2    1 * PI/2    2 * PI/2    3 * PI/2    4 * PI/2
    //             +1
    // 0                       0                       0
    //                                     -1
    
    if (HALF_PI_x_0 <= phase && phase < HALF_PI_x_1) {
        return phase / HALF_PI_x_1; // 0 ... 1
    }
    
    if (HALF_PI_x_1 <= phase && phase < HALF_PI_x_3) {
        return 2 - phase / HALF_PI_x_1; // 1 ... -1
    }

    if (HALF_PI_x_3 <= phase && phase < HALF_PI_x_4) {
        return -4 + phase / HALF_PI_x_1; // -1 ... 0
    }

    std::cout << std::setprecision(64) << "Invalid phase passed to render_triangle_wave() " << phase << std::endl;
    return 0;
}

static double render_wave(Wave wave, double phase) {
    switch (wave) {
        case Wave::Sine:
            return render_sine_wave(phase);
        case Wave::Square:
            return render_square_wave(phase);
        case Wave::Triangle:
            return render_triangle_wave(phase);
        default:
            return 0;
    }
}

static double next_phase(double phase, double frequency, unsigned sample_rate) {
    double next_phase = phase + PI_x_2 * frequency / sample_rate;

    if (next_phase >= PI_x_2) {
        next_phase -= PI_x_2;
    }

    if (next_phase < 0.0) {
        next_phase += PI_x_2;
    }

    return next_phase;
}

struct audiostation::OscillatorImpl {
    OscillatorConfig config;
    bool is_live;
};

audiostation::Oscillator::Oscillator(OscillatorConfig config) {
    this->impl = std::make_unique<OscillatorImpl>();
    this->impl->config = config;
    this->impl->is_live = false;
}

Oscillator::Oscillator(const Oscillator& other) {
    this->impl = std::make_unique<OscillatorImpl>();
    this->impl->config = other.impl->config;
    this->impl->is_live = other.impl->is_live;
}

audiostation::Oscillator::Oscillator(Oscillator&& other) : 
    impl(std::move(other.impl))
{ }

audiostation::Oscillator::~Oscillator() {
    this->impl.reset();
}

void audiostation::Oscillator::trigger(Note note) {
    this->impl->is_live = true;
}

void audiostation::Oscillator::release(Note note) {
    this->impl->is_live = false;
}

void audiostation::Oscillator::set_amplitude(double amplitude) {
    this->impl->config.amplitude = amplitude;
}

void audiostation::Oscillator::set_frequency(double frequency) {
    this->impl->config.frequency = frequency;
}

void audiostation::Oscillator::set_phase(double phase) {
    this->impl->config.phase = phase;
}

double audiostation::Oscillator::get_amplitude() const {
    return this->impl->config.amplitude;
}

double audiostation::Oscillator::get_frequency() const {
    return this->impl->config.frequency;
}

double audiostation::Oscillator::get_phase() const {
    return this->impl->config.phase;
}

bool audiostation::Oscillator::is_live() const {
    return this->impl->is_live;
}

double audiostation::Oscillator::render() {
    if (!this->impl->is_live) {
        return 0;
    }

    auto& config = this->impl->config;
    double sample = render_wave(config.wave, config.phase) * config.amplitude;
    config.phase = next_phase(config.phase, config.frequency, config.sample_rate);
    return sample;
}
