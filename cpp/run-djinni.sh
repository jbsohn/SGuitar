djinni/src/run \
    --java-out src/generated/java \
    --cpp-out src/generated/cpp \
    --jni-out src/generated/jni \
    --objc-out src/generated/objc \
    --objcpp-out src/generated/objc-out \
    --java-package com.steelsidekick.sguitar \
    --ident-jni-class NativeFooBar \
    --objc-type-prefix SG \
    --idl ./idl/sguitar.djinni
