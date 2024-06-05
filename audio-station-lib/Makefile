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
	src/notes.cpp \
	src/oscillator.cpp \
	src/renderer.cpp \
	src/synth.cpp \
	src/track.cpp \
	test/asserts.cpp \
	test/delay-tests.cpp \
	test/oscillator-tests.cpp \
	test/renderer-tests.cpp \
	test/synth-tests.cpp \
	test/track-tests.cpp \
	test/main.cpp

.PHONY: run
run:
	./audio-station
