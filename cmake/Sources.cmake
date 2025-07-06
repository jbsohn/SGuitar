# Source files
set(SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/ChordDAOImpl.cpp
        ${PROJECT_SOURCE_DIR}/src/ChordImpl.cpp
        ${PROJECT_SOURCE_DIR}/src/DatabaseConnectionImpl.cpp
        ${PROJECT_SOURCE_DIR}/src/GuitarAdjustmentImpl.cpp
        ${PROJECT_SOURCE_DIR}/src/GuitarDAOImpl.cpp
        ${PROJECT_SOURCE_DIR}/src/GuitarFactory.cpp
        ${PROJECT_SOURCE_DIR}/src/GuitarImpl.cpp
        ${PROJECT_SOURCE_DIR}/src/GuitarImport.cpp
        ${PROJECT_SOURCE_DIR}/src/GuitarStringImpl.cpp
        ${PROJECT_SOURCE_DIR}/src/HarmonizedScaleImpl.cpp
        ${PROJECT_SOURCE_DIR}/src/NoteImpl.cpp
        ${PROJECT_SOURCE_DIR}/src/ScaleDAOImpl.cpp
        ${PROJECT_SOURCE_DIR}/src/ScaleImpl.cpp
        ${PROJECT_SOURCE_DIR}/src/StringAdjustmentImpl.cpp
        ${PROJECT_SOURCE_DIR}/src/Utility.cpp
)

set(TEST_SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/tests/src/main.cpp
        ${PROJECT_SOURCE_DIR}/tests/src/TestChord.cpp
        ${PROJECT_SOURCE_DIR}/tests/src/TestDAO.cpp
        ${PROJECT_SOURCE_DIR}/tests/src/TestFactory.cpp
        ${PROJECT_SOURCE_DIR}/tests/src/TestGuitar.cpp
        ${PROJECT_SOURCE_DIR}/tests/src/TestGuitarObjects.cpp
        ${PROJECT_SOURCE_DIR}/tests/src/TestImport.cpp
        ${PROJECT_SOURCE_DIR}/tests/src/TestNote.cpp
        ${PROJECT_SOURCE_DIR}/tests/src/TestScale.cpp
)
set(DJINNI_CPP
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/cpp/DataRef.cpp
)
set(DJINNI_OBJC
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/objc/DJFuture.mm
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/objc/DJIError.mm
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/objc/DJIProxyCaches.mm
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/objc/DJOutcome.mm

)
set(DJINNI_JNI
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/jni/DataRef_jni.cpp
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/jni/Future_jni.cpp
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/jni/djinni_main.cpp
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/jni/djinni_support.cpp
)
set(DJINNI_WASM
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/wasm/DataRef_wasm.cpp
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/wasm/djinni_wasm.cpp
)
set(FRAMEWORK_INCLUDE
        ${PROJECT_SOURCE_DIR}/framework-include/SGuitar.h
)
set(DJINNI_IDL ${PROJECT_SOURCE_DIR}/idl/sguitar.djinni)

# generated source by DJINNI
file(GLOB GENERATED_CPP "generated-src/cpp/*.cpp")
file(GLOB GENERATED_OBJC "generated-src/objc/*.mm")
file(GLOB GENERATED_OBJC_CPP "generated-src/objc-cpp/*.mm")
file(GLOB GENERATED_JNI "generated-src/jni/*.cpp")
file(GLOB GENERATED_WASM "generated-src/wasm/*.cpp")
file(GLOB DJINNI_OBJC_HEADER "generated-src/objc/*.h")

set(FRAMEWORK_PUBLIC_HEADER
        ${DJINNI_OBJC_HEADER}
        ${FRAMEWORK_INCLUDE}
)