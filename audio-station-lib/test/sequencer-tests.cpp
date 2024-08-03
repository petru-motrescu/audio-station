#include "sequencer.hpp"
#include "asserts.hpp"
#include "test-suite.hpp"
using namespace audiostation;

struct DummyPlayable : public Playable {

    void trigger(Note note) { 
        this->calls.push_back(std::make_pair(note, true));
    };

    void release(Note note) { 
        this->calls.push_back(std::make_pair(note, false));
    };

    void debug() {
        for (auto& call : calls) {
            std::cout << Notes::to_string(call.first) << " : " << call.second << ", ";
        }

        std::cout << std::endl;
    }

    std::vector<std::pair<Note, bool>> calls;
};

void audiostation::TestSuite::run_sequencer_tests() {

    test("Sequencer note hold", [] {
        DummyPlayable playable;
        Sequencer sequencer({ 
            .output = &playable,
            .blocks = {
                SequenceBlock({
                    .notes = {
                        SequenceNote({ .note = Note::C1, .length = 2, .offset = 0 }),
                        SequenceNote({ .note = Note::C2, .length = 2, .offset = 2 })
                    }
                })
            },
        });

        sequencer.trigger();
        sequencer.render();
        sequencer.render();

        std::vector<std::pair<Note, bool>> expected_calls({
            std::make_pair(Note::C1, true)
        });

        assert_equal<std::pair<Note, bool>>(expected_calls, playable.calls);
    });

    test("Sequencer note change", [] {
        DummyPlayable playable;
        Sequencer sequencer({ 
            .output = &playable,
            .blocks = {
                SequenceBlock({
                    .notes = {
                        SequenceNote({ .note = Note::C1, .length = 2, .offset = 0 }),
                        SequenceNote({ .note = Note::C2, .length = 2, .offset = 2 })
                    }
                })
            },
        });

        sequencer.trigger();
        sequencer.render();
        sequencer.render();
        sequencer.render();

        std::vector<std::pair<Note, bool>> expected_calls({
            std::make_pair(Note::C1, true),
            std::make_pair(Note::C1, false),
            std::make_pair(Note::C2, true),
        });

        assert_equal<std::pair<Note, bool>>(expected_calls, playable.calls);
    });

    test("Sequencer loop of illegal length", [] {
        bool exception_thrown = false;
        try {
            Sequencer sequencer({ 
                .loop_enabled = true,
                .loop_length = 1,
            });
        }
        catch (...) {
            exception_thrown = true;
        }

        assert_true(exception_thrown);
    });

    test("Sequencer loop of minimum length", [] {
        DummyPlayable playable;
        Sequencer sequencer({ 
            .output = &playable,
            .blocks = { SequenceBlock({ .notes = { SequenceNote() } }) },
            .loop_enabled = true,
            .loop_length = 2
        });

        sequencer.trigger();
        sequencer.render();
        sequencer.render();
        sequencer.render();

        std::vector<std::pair<Note, bool>> expected_calls({
            std::make_pair(Note::C4, true),
            std::make_pair(Note::C4, false),
            std::make_pair(Note::C4, true),
        });

        assert_equal<std::pair<Note, bool>>(expected_calls, playable.calls);
    });

    test("Sequencer loop of 2 notes", [] {
        DummyPlayable playable;
        Sequencer sequencer({ 
            .output = &playable,
            .blocks = {
                SequenceBlock({
                    .notes = {
                        SequenceNote({ .note = Note::C1, .offset = 0 }),
                        SequenceNote({ .note = Note::C2, .offset = 1 })
                    }
                })
            },
            .loop_length = 3
        });

        sequencer.trigger();
        sequencer.render();
        sequencer.render();
        sequencer.render();
        sequencer.render();

        std::vector<std::pair<Note, bool>> expected_calls({
            std::make_pair(Note::C1, true),
            std::make_pair(Note::C1, false),
            std::make_pair(Note::C2, true),
            std::make_pair(Note::C2, false),
            std::make_pair(Note::C1, true),
        });

        assert_equal<std::pair<Note, bool>>(expected_calls, playable.calls);
    });

}
