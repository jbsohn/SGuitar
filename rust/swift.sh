cargo build --release
cargo run --bin uniffi-bindgen generate --library target/release/libsguitar.a --language swift --out-dir swift
swiftc \
    -module-name sguitar \
    -emit-library -o libsguitar.a \
    -emit-module -emit-module-path ./ \
    -parse-as-library \
    -L ./target/release/ \
    -lsguitar \
    -Xcc -fmodule-map-file=./swift/sguitarFFI.modulemap \
    swift/sguitar.swift \
