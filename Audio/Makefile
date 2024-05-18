.PHONY: build
build:
	g++ -std=c++20 -Wall -O2 \
	-Iinc \
	-Itest \
	-framework AudioUnit \
	-framework AudioToolbox \
	-o audio-station \
	src/audio-station.cpp \
	src/audio-renderer.cpp \
	src/notes.cpp \
	src/oscillator.cpp \
	src/synth.cpp \
	src/wave-renderer.cpp \
	test/asserts.cpp \
	test/audio-renderer-tests.cpp \
	test/oscillator-tests.cpp \
	test/synth-tests.cpp \
	test/wave-renderer-tests.cpp \
	test/main.cpp

.PHONY: run
run:
	./audio-station
