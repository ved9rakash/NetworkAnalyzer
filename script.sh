#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Define the path to the vcpkg toolchain file
VCPKG_TOOLCHAIN_FILE="/home/ved9rakash/vcpkg/scripts/buildsystems/vcpkg.cmake"

# Run CMake with the specified preset and toolchain file
cmake --preset=default -DCMAKE_TOOLCHAIN_FILE="${VCPKG_TOOLCHAIN_FILE}" --log-level="VERBOSE"

# Build the project using make
make -C ./cmake/build-debug/

# Run the built executable
./cmake/build-debug/src/network_analyzer
