#!/bin/sh

if [ -z "$3" ]
then
  echo "Usage: <djinni path> <generated-src> <idl>"
  exit 1
fi

DJINNI=$1
GENERATED_SRC=$2
IDL=$3

rm -rf "$GENERATED_SRC"
$DJINNI \
    --java-out "$GENERATED_SRC"/java \
    --cpp-out "$GENERATED_SRC"/cpp \
    --jni-out "$GENERATED_SRC"/jni \
    --objc-out "$GENERATED_SRC"/objc \
    --objcpp-out "$GENERATED_SRC"/objc-cpp \
    --java-package com.steelsidekick.sguitar \
    --ident-jni-class NativeSGuitar \
    --objc-type-prefix SG \
    --idl "$IDL"
