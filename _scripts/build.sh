#! /bin/sh

cmake.exe -DCMAKE_CONFIGURATION_TYPES=Release -S ./Sandbox -B _out/config/Release
cmake --build _out/config/Release --config=Release -j 8