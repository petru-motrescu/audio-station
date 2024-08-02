#include "sequencer.hpp"
#include "asserts.hpp"
#include "test-suite.hpp"
using namespace audiostation;

struct DummyPlayer : public Player {

    void play(Note note) { 
        this->calls.push_back(std::make_pair(note, true));
    };

    void stop(Note note) { 
        this->calls.push_back(std::make_pair(note, false));
    };

    std::vector<std::pair<Note, bool>> calls;
};

void audiostation::TestSuite::run_sequencer_tests() {

    test("Sequencer step hold", [] {
        DummyPlayer player;
        Sequencer sequencer({ 
            .outputs = { &player },
            .step_duration = 1,
            .steps = {
                { .note = Note::C1, .level = 1.0 },
                { .note = Note::C2, .level = 1.0 },
            },
            .sample_rate = 3000 // so that we get 3 ticks per step
        });

        sequencer.trigger();
        sequencer.tick();
        sequencer.tick();
        sequencer.tick();

        std::vector<std::pair<Note, bool>> expected_calls({
            std::make_pair(Note::C1, true)
        });

        assert_equal<std::pair<Note, bool>>(expected_calls, player.calls);
    });

    test("Sequencer step change", [] {
        DummyPlayer player;
        Sequencer sequencer({ 
            .outputs = { &player },
            .step_duration = 1,
            .steps = {
                { .note = Note::C1, .level = 1.0 },
                { .note = Note::C2, .level = 1.0 },
            },
            .sample_rate = 3000 // so that we get 3 ticks per step
        });

        sequencer.trigger();
        sequencer.tick();
        sequencer.tick();
        sequencer.tick();
        sequencer.tick();

        std::vector<std::pair<Note, bool>> expected_calls({
            std::make_pair(Note::C1, true),
            std::make_pair(Note::C1, false),
            std::make_pair(Note::C2, true),
        });

        assert_equal<std::pair<Note, bool>>(expected_calls, player.calls);
    });

    test("Sequencer step loop", [] {
        DummyPlayer player1;
        DummyPlayer player2;
        Sequencer sequencer({ 
            .outputs = { &player1, &player2 },
            .step_duration = 1,
            .steps = {
                { .note = Note::C1, .level = 1.0 },
                { .note = Note::C2, .level = 1.0 },
            },
            .sample_rate = 1000 // so that we get 1 tick per step
        });

        sequencer.trigger();
        sequencer.tick();
        sequencer.tick();
        sequencer.tick();

        std::vector<std::pair<Note, bool>> expected_calls({
            std::make_pair(Note::C1, true),
            std::make_pair(Note::C1, false),
            std::make_pair(Note::C2, true),
            std::make_pair(Note::C2, false),
            std::make_pair(Note::C1, true),
        });

        assert_equal<std::pair<Note, bool>>(expected_calls, player1.calls);
        assert_equal<std::pair<Note, bool>>(expected_calls, player2.calls);
    });

}
