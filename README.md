# SGuitar

# iOS

cmake -B ios-build -G Xcode -DCMAKE_TOOLCHAIN_FILE=ios.toolchain.cmake -DPLATFORM=OS64
cmake --build ios-build --config Release
