#include <iostream>
#include <cmath>
#include <iomanip>
#include <random>
#include "wave-renderer.hpp"
using namespace audiostation;

constexpr double PI_x_2 = 2 * M_PI;
constexpr double HALF_PI = M_PI / 2;
constexpr double HALF_PI_x_0 = 0;
constexpr double HALF_PI_x_1 = HALF_PI;
constexpr double HALF_PI_x_3 = 3 * M_PI / 2;
constexpr double HALF_PI_x_4 = PI_x_2;

static std::random_device noise_device;
static std::mt19937 noise_generator(noise_device());

double render_sine_wave(double phase) {
    return sin(phase);
}

double render_square_wave(double phase) {
    // TODO Calculate without sin() call
    if (sin(phase) < 0) {
        return -1;
    } else {
        return +1;
    }
}

double render_triangle_wave(double phase) {
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

double render_noise_wave() {
    std::uniform_real_distribution<> distribution(0, PI_x_2);
    return sin(distribution(noise_generator));
}

double audiostation::WaveRenderer::render(Wave wave, double phase) {
    switch (wave) {
        case Wave::Sine:
            return render_sine_wave(phase);
        case Wave::Square:
            return render_square_wave(phase);
        case Wave::Triangle:
            return render_triangle_wave(phase);
        case Wave::Noise:
            return render_noise_wave();
        default:
            return 0;
    }
}

double audiostation::WaveRenderer::next_phase(double phase, double frequency, unsigned sample_rate) {
    double next_phase = phase + PI_x_2 * frequency / sample_rate;

    if (next_phase >= PI_x_2) {
        next_phase -= PI_x_2;
    }

    if (next_phase < 0.0) {
        next_phase += PI_x_2;
    }

    return next_phase;
}
