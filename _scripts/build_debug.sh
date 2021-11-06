#! /bin/sh

cmake.exe -DCMAKE_CONFIGURATION_TYPES=Debug -S ./Sandbox -B _out/config/Debug
cmake --build _out/config/Debug --config=Debug -j 8