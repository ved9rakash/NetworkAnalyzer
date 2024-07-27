#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e
#testing

rm -rf cmake
cmake --preset default --log-level=VERBOSE
ninja -C cmake/build-debug/ --verbose
sudo ./cmake/build-debug/src/network_analyzer