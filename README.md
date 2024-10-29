# SGuitar

# iOS

cmake -B build -G Xcode -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/ios.toolchain.cmake -DPLATFORM=OS64
cmake --build build --config Release
