#!/bin/sh
if (NOT DEFINED DJINNI_RUN)
    message(FATAL_ERROR "DJINNI_RUN is not set")
endif ()

if (NOT DEFINED DJINNI_GENERATED_SRC)
    message(FATAL_ERROR "DJINNI_GENERATED_SRC is not set")
endif ()

if (NOT DEFINED DJINNI_IDL)
    message(FATAL_ERROR "DJINNI_IDL is not set")
endif ()

message(STATUS "generating DJINNI source with these options:")
message(STATUS "DJINNI_RUN: ${DJINNI_RUN}")
message(STATUS "DJINNI_GENERATED_SRC: ${DJINNI_GENERATED_SRC}")
message(STATUS "DJINNI_IDL: ${DJINNI_IDL}")

file(REMOVE_RECURSE ${DJINNI_GENERATED_SRC})
execute_process(
        COMMAND ${DJINNI_RUN} --java-out "${DJINNI_GENERATED_SRC}/java/com/steelsidekick/sguitar"
        --java-package com.steelsidekick.sguitar
        --ident-java-field mFooBar
        --cpp-out "${DJINNI_GENERATED_SRC}/cpp"
        --jni-out "${DJINNI_GENERATED_SRC}/jni"
        --ident-jni-class JNIFooBar
        --ident-jni-file jni_foo_bar
        --objc-out "${DJINNI_GENERATED_SRC}/objc"
        --objc-type-prefix SG
        --objcpp-out "${DJINNI_GENERATED_SRC}/objc-cpp"
        --idl "${DJINNI_IDL}"
)
