#!/bin/sh

clang++ -std=c++20 -Wall -O2 \
	-I../lib/inc \
	-L../lib/bin \
	-framework AudioUnit \
	-framework AudioToolbox \
	-l audiostation \
	-o audiostation-tests \
	asserts.cpp \
	delay-tests.cpp \
	main.cpp \
	mixer-tests.cpp \
	noise-tests.cpp \
	oscillator-tests.cpp \
	sequencer-tests.cpp \
	synth-tests.cpp \
	test-suite.cpp

./audiostation-tests
