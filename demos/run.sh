#!/bin/sh

clang++ -std=c++20 -Wall -O2 \
	-I../lib/inc \
	-L../lib/bin \
	-framework AudioUnit \
	-framework AudioToolbox \
	-l audiostation \
	-o audiostation-demos \
	drum-demo.cpp \
	main.cpp \
	mixer-demo.cpp \
	noise-demo.cpp \
	oscillator-demo.cpp \
	sequencer-demo.cpp \
	synth-demo.cpp

./audiostation-demos
