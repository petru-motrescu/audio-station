.PHONY: build
build:
	g++ -std=c++20 -Wall -O2 \
	-Iinc \
	-Itest \
	-framework AudioUnit \
	-framework AudioToolbox \
	-o audio-station \
	src/audio-station.cpp \
	src/delay.cpp \
	src/drum.cpp \
	src/envelope.cpp \
	src/noise.cpp \
	src/notes.cpp \
	src/oscillator.cpp \
	src/project.cpp \
	src/reverb.cpp \
	src/sequencer.cpp \
	src/synth.cpp \
	src/utils.cpp \
	test/asserts.cpp \
	test/delay-tests.cpp \
	test/main.cpp \
	test/noise-tests.cpp \
	test/oscillator-tests.cpp \
	test/project-tests.cpp \
	test/sequencer-tests.cpp \
	test/synth-tests.cpp \
	test/test-suite.cpp

.PHONY: run
run:
	./audio-station
