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
	src/envelope-renderer.cpp \
	src/noise.cpp \
	src/notes.cpp \
	src/oscillator.cpp \
	src/reverb.cpp \
	src/synth.cpp \
	src/track.cpp \
	src/utils.cpp \
	src/wave-renderer.cpp \
	test/asserts.cpp \
	test/delay-tests.cpp \
	test/main.cpp \
	test/noise-tests.cpp \
	test/oscillator-tests.cpp \
	test/synth-tests.cpp \
	test/test-suite.cpp \
	test/track-tests.cpp \
	test/wave-renderer-tests.cpp

.PHONY: run
run:
	./audio-station
