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
	src/wave-rendering.cpp \
	test/wave-rendering-tests.cpp \
	test/main.cpp

.PHONY: run
run:
	./audio-station
