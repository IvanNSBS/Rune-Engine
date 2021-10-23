#! /bin/sh

cmake.exe -DGLFW_BUILD_DOCS=OFF -DCMAKE_CONFIGURATION_TYPES=Release -S ./RuneRenderer -B _out/config/Release
cmake --build _out/config/Release --config=Release --target=Engine -j 8
./_out/build/Release/RuneRenderer.exe