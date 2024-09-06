cargo build --release --lib --target aarch64-apple-darwin
cargo build --release --lib --target x86_64-apple-darwin
cargo run --bin uniffi-bindgen generate src/sguitar.udl --language swift --out-dir swift

rm -rf swift/include
mkdir swift/include
cp swift/sguitar.swift include
cp swift/sguitarFFI.h swift/include
cp swift/sguitarFFI.modulemap swift/include/module.modulemap
cp swift/sguitar.swift swift/include

#rm -rf libs/libsguitar-macos.a
#rm -rf libs/libsguitar-maccatalyst.a
rm -rf swift/libs
mkdir swift/libs
lipo -create -output swift/libs/libsguitar-macos.a target/aarch64-apple-darwin/release/libsguitar.a target/x86_64-apple-darwin/release/libsguitar.a
#lipo -create -output libs/libsguitar-maccatalyst.a \
#      target/aarch64-apple-ios-macabi/release/libsguitar.a \
#      target/x86_64-apple-ios-macabi/release/libsguitar.a

rm -rf SGuitarFFI.xcframework
xcodebuild -create-xcframework -library swift/libs/libsguitar-macos.a -headers swift/include -output SGuitarFFI.xcframework

#cargo build --release
#cargo run --bin uniffi-bindgen generate src/sguitar.udl --language swift --out-dir swift
#swiftc \
#    -module-name sguitar \
#    -emit-library -o libsguitar.a \
#    -emit-module -emit-module-path ./ \
#    -parse-as-library \
#    -L ./target/release/ \
#    -lsguitar \
#    -Xcc -fmodule-map-file=./swift/sguitarFFI.modulemap \
#    swift/sguitar.swift
#mv libsguitar.a swift
#mv sguitar.swiftmodule swift
#mv .swiftdoc swift
#mv .swiftsourceinfo swift




