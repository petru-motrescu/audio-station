#include <iostream>
#include <queue>
#include "config.hpp"
#include "delay.hpp"
#include "utils.hpp"
using namespace audiostation;

struct audiostation::DelayImpl {
    DelayConfig config;
    std::queue<double> input_history;
    unsigned history_size;
};

audiostation::Delay::Delay() : Delay(DelayConfig()) { }

audiostation::Delay::Delay(DelayConfig config) {
    this->impl = std::make_unique<DelayImpl>();
    this->impl->config = config;
    this->impl->history_size = config.time * Config::SAMPLE_RATE / 1000.0;

    for (int i = 0; i < this->impl->history_size; i++) {
        this->impl->input_history.emplace(0);
    }
}

audiostation::Delay::~Delay() {
    this->impl.reset();
}

double audiostation::Delay::render(double sample) {
    double result = this->impl->input_history.front() * this->impl->config.level;
    this->impl->input_history.pop();
    this->impl->input_history.emplace(sample);
    return result;
}
