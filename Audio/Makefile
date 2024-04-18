.PHONY: build
build:
	g++ -std=c++20 -Wall -O2 \
	-Iinc \
	-Itest \
	-o audio-station \
	src/wave-rendering.cpp \
	test/wave-rendering-tests.cpp \
	test/main.cpp

.PHONY: run
run:
	./audio-station
