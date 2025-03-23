# SGuitar

# DJINNI

To regenerate the djinni files, run the following command:

```
cmake -DDJINNI=./djinni -DDJINNI_GENERATED_SRC=./generated-src -DDJINNI_IDL=./idl/sguitar.djinni -P ./cmake/run-djinni.cmake
```

# Integration Testing

Usage: <path-to-ddl> <path-to-lap-steel> <path-to-pedal-steel>

These arguments get passed into DocTest app when running the integration tests:

```
$ProjectFileDir$/db/ddl.sql "$ProjectFileDir$/import/Lap Steel" "$ProjectFileDir$/import/Pedal Steel"
```

# iOS Framework Target
```
cmake -S . -B build -G Xcode -DIOS=1
```

# EMSCRIPTEN WebAssembly Target

// Compiles the source code using the Embind bindings to connect C/C++ and JavaScript

--bind

// Switch to using the much smaller implementation

-s MALLOC=emmalloc

// Allows us to manually invoke the initialization of wasm

-s MODULARIZE=1

// We need to pass int64_t

-s WASM_BIGINT=1

```
emcmake cmake -S . -B .build
cd .build
emmake make
```
