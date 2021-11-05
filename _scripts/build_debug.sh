#! /bin/sh

cmake.exe -DGLFW_BUILD_DOCS=OFF -DCMAKE_CONFIGURATION_TYPES=Debug -S ./RuneFramework -B _out/config/Debug
cmake --build _out/config/Debug --config=Debug --target=Engine -j 8