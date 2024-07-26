#!/bin/sh

# Clean the build directory
cmake --build cmake/build-debug --target clear
cmake --preset default
