#include <iostream>
#include <functional>
#include <string>

extern void combo_demo();
extern void delay_demo();
extern void drum_demo();
extern void mixer_demo();
extern void noise_demo();
extern void oscillator_demo();
extern void reverb_demo();
extern void sequencer_demo();
extern void song_demo();
extern void synth_demo();

struct Demo {
    std::function<void()> run;
    std::string name;
};

int main() {
    std::vector<Demo> demos = {
        { song_demo, "song" },
        { combo_demo, "combo" },
        { delay_demo, "delay" },
        { drum_demo, "drum" },
        { mixer_demo, "mixer" },
        { noise_demo, "noise" },
        { oscillator_demo, "oscillator" },
        { reverb_demo, "reverb" },
        { sequencer_demo, "sequencer" },
        { synth_demo, "synth" },
    };

    for (auto& demo : demos) {
        std::cout << "🧪 Running " << demo.name << " demo" << std::endl;
        demo.run();
        std::cout << std::endl;
    }

    return 0;
}
