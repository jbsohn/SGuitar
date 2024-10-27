#!/bin/sh
rm -rf generated-src
./djinni/src/run \
    --java-out generated-src/java \
    --cpp-out generated-src/cpp \
    --jni-out generated-src/jni \
    --objc-out generated-src/objc \
    --objcpp-out generated-src/objc-cpp \
    --java-package com.steelsidekick.sguitar \
    --ident-jni-class NativeSGuitar \
    --objc-type-prefix SG \
    --idl ./idl/sguitar.djinni
