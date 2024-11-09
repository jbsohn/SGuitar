# SGuitar

# DJINNI

```
cmake -DDJINNI_RUN=./djinni/src/run -DDJINNI_GENERATED_SRC=./generated-src -DDJINNI_IDL=./idl/sguitar.djinni -P ./scripts/run-djinni.cmake
```

# iOS

To setup Xcode project for iOS framework:

```
cmake -S . -B build -G Xcode -DTARGET=iOS
```
