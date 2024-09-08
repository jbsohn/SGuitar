# build Rust release mode target for x64 and Arch64
cargo build --release --lib --target aarch64-apple-darwin
cargo build --release --lib --target x86_64-apple-darwin

# generate Rust Swift bindings
rm -rf build
cargo run --bin uniffi-bindgen generate src/sguitar.udl --language swift --out-dir build

# setup bindings into usable paths
mkdir build/include
cp build/sguitarFFI.h build/include
cp build/sguitarFFI.modulemap build/include/module.modulemap
lipo -create -output build/libsguitar-macos.a target/aarch64-apple-darwin/release/libsguitar.a target/x86_64-apple-darwin/release/libsguitar.a
xcodebuild -create-xcframework -library build/libsguitar-macos.a -headers build/include -output build/SGuitarFFI.xcframework

mkdir -p lib
cp -rf build/SGuitarFFI.xcframework lib
cp build/SGuitar.swift lib
rm -rf build
