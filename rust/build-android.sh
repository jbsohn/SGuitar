cargo ndk -t armeabi-v7a -t arm64-v8a -t x86_64 -o ./android build

# generate Rust Swift bindings
cargo run --bin uniffi-bindgen generate src/sguitar.udl --language kotlin --out-dir ./android
