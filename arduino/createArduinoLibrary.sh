#!/bin/sh

cp ../src/led_strip.h .
cp ../src/led_strip.c led_strip.cpp
cp ../src/led_strip_no_backend.c led_strip_no_backend.cpp
cp ../src/led_strip_no_backend.h .
cp ../src/led_strip-cpp.h .
cp ../src/led_strip-cpp-implementation.h .
cp ../src/led_strip_struct.h .

zip -r LedStrip.zip * -x createArduinoLibrary.sh
