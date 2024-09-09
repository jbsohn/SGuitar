# build Rust debug mode targets for x64 and Arch64
cargo build --lib --target aarch64-apple-darwin
cargo build --lib --target x86_64-apple-darwin
cargo build --lib --target aarch64-apple-ios-sim
cargo build --lib --target x86_64-apple-ios

# generate Rust Swift bindings
rm -rf build
cargo run --bin uniffi-bindgen generate src/sguitar.udl --language swift --out-dir build

# setup bindings into usable paths
mkdir build/include
cp build/sguitarFFI.h build/include
cp build/sguitarFFI.modulemap build/include/module.modulemap
lipo -create -output build/libsguitar-macos.a target/aarch64-apple-darwin/debug/libsguitar.a target/x86_64-apple-darwin/debug/libsguitar.a
lipo -create -output build/libsguitar-ios.a target/aarch64-apple-ios-sim/debug/libsguitar.a target/x86_64-apple-ios/debug/libsguitar.a
xcodebuild -create-xcframework -library build/libsguitar-macos.a -library build/libsguitar-ios.a -headers build/include -output build/SGuitarFFI.xcframework

mkdir -p lib
cp -rf build/SGuitarFFI.xcframework lib
cp build/SGuitar.swift lib
rm -rf build
