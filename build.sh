#!/bin/sh

set -e
set -x
rm -rf bin
rm -rf build
mkdir bin
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release ..
make
cd ..
cp build/demos/audiostation-demos bin/audiostation-demos
cp build/tests/audiostation-tests bin/audiostation-tests
cp build/lib/libaudiostation.a bin/libaudiostation.a
{ set +x; } 2>/dev/null
echo DONE 🥁