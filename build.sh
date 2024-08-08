#!/bin/sh

set -e
set -x
rm -rf bin
rm -rf build
mkdir bin
mkdir build
cd build
cmake ..
make
cd ..
cp build/demos/audiostation-demos bin/audiostation-demos
cp build/tests/audiostation-tests bin/audiostation-tests
cp build/lib/libaudiostation.a bin/libaudiostation.a
{ set +x; } 2>/dev/null
echo DONE 🥁