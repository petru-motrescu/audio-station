#!/bin/sh

clang++ -std=c++20 -Wall -O2 \
	-I../lib/inc \
	-L../lib/bin \
	-framework AudioUnit \
	-framework AudioToolbox \
	-l audiostation \
	-o audiostation-demos \
	main.cpp

./audiostation-demos
