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
        COMMAND ${DJINNI_RUN} --java-out "${DJINNI_GENERATED_SRC}/java"
        --cpp-out "${DJINNI_GENERATED_SRC}/cpp"
        --jni-out "${DJINNI_GENERATED_SRC}/jni"
        --objc-out "${DJINNI_GENERATED_SRC}/objc"
        --objcpp-out "${DJINNI_GENERATED_SRC}/objc-cpp"
        --java-package com.steelsidekick.sguitar
        --ident-jni-class NativeSGuitar
        --objc-type-prefix SG
        --idl "${DJINNI_IDL}"
)
