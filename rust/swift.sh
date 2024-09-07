# build Rust release mode target for x64 and Arch64
cargo build --release --lib --target aarch64-apple-darwin
cargo build --release --lib --target x86_64-apple-darwin

# generate Rust Swift bindings
cargo run --bin uniffi-bindgen generate src/sguitar.udl --language swift --out-dir swift

# setup bindings into usable paths
rm -rf swift/include
mkdir swift/include
cp swift/sguitarFFI.h swift/include
cp swift/sguitarFFI.modulemap swift/include/module.modulemap
rm swift/libsguitar-macos.a
lipo -create -output swift/libsguitar-macos.a target/aarch64-apple-darwin/release/libsguitar.a target/x86_64-apple-darwin/release/libsguitar.a

rm -rf swift/SGuitarFFI.xcframework
xcodebuild -create-xcframework -library swift/libsguitar-macos.a -headers swift/include -output swift/SGuitarFFI.xcframework

### tagged for deletion...
#swiftc \
#    -module-name sguitar \
#    -emit-library -o libsguitar.a \
#    -emit-module -emit-module-path ./ \
#    -parse-as-library \
#    -L ./target/release/ \
#    -lsguitar \
#    -Xcc -fmodule-map-file=./swift/sguitarFFI.modulemap \
#    swift/sguitar.swift
