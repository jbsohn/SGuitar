djinni/src/run \
    --java-out cpp/generated/java \
    --java-package com.steelsidekick.sguitar \
    --cpp-out cpp/generated/cpp \
    --jni-out cpp/generated/jni \
    --ident-jni-class NativeFooBar \
    --objc-out cpp/generated/objc \
    --objc-type-prefix SG \
    --objcpp-out cpp/generated/objc-out \
    --idl ./idl/sguitar.djinni
