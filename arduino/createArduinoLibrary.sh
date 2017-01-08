#!/bin/sh

cp ../led_strip.h .
cp ../led_strip.c led_strip.cpp
cp ../led_strip_no_backend.c led_strip_no_backend.cpp
cp ../led_strip_no_backend.h .
cp ../led_strip-cpp.h .
cp ../led_strip-cpp-implementation.h .
cp ../led_strip_struct.h .

zip -r LedStrip.zip * -x setup.sh
