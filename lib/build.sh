#!/bin/sh

FILES=(
	"audio-station-c"
	"audio-station"
	"delay"
	"drum"
	"envelope"
	"mixer"
	"noise"
	"notes"
	"oscillator"
	"reverb"
	"sequencer"
	"synth"
	"utils"
)

# Append the .o postfix to all strings in the array
OBJ_FILES=( "${FILES[@]/%/.o}" )

# Prepend the /bin prefix to all strings in the array
OBJ_FILES=( "${OBJ_FILES[@]/#/bin/}" )

rm -rf bin
mkdir bin

# Compile
for file in ${FILES[*]};
	do clang++ -c -std=c++20 -Wall -O2 -Iinc src/$file.cpp -o bin/$file.o;
done

# Generate static library
ar -rcs bin/libaudiostation.a ${OBJ_FILES[*]}

rm bin/*.o
