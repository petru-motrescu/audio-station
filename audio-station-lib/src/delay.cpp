#include <iostream>
#include <iomanip>
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

audiostation::Delay::Delay(Delay&& other) : impl(std::move(other.impl)) { }

audiostation::Delay::Delay(DelayConfig config) {
    require(config.feedback >= 0.0, "Delay feedback cannot be negative");
    require(config.feedback <= 1.0, "Delay feedback cannot be greater than 1.0");

    if (config.time == 0) {
        std::cout << "Delay time is 0" << std::endl;
    }

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
    if (this->impl->input_history.size() == 0) {
        return 0;
    }

    double result = this->impl->input_history.front();
    double snapshot = (sample + this->impl->config.feedback * result) * this->impl->config.level;

    if (snapshot > Config::MAX_AMPLITUDE) {
        snapshot = Config::MAX_AMPLITUDE;
    }
    
    if (snapshot < Config::MIN_AMPLITUDE) {
        snapshot = Config::MIN_AMPLITUDE;
    }

    this->impl->input_history.pop();
    this->impl->input_history.emplace(snapshot);

    if (this->impl->config.debug) {
        std::cout << std::fixed << std::setprecision(16) 
            << "Delay sample:" << sample 
            << ", result:" << result 
            << ", snapshot:" << snapshot 
            << std::endl;
    }

    return result;
}
