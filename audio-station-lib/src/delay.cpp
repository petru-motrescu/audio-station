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
    require(config.feedback >= 0.0, "Delay feedback cannot be negative");
    require(config.feedback <= 1.0, "Delay feedback cannot be greater than 1.0");

    this->impl = std::make_unique<DelayImpl>();
    this->impl->config = config;
    this->impl->history_size = config.time * config.sample_rate / 1000.0;

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
    double snapshot = sample + this->impl->config.feedback * result;
    this->impl->input_history.emplace(snapshot);
    if (this->impl->config.debug) {
        std::cout << "Delay sample:" << sample << ", result:" << result << ", snapshot:" << snapshot << std::endl;
    }
    return result;
}
