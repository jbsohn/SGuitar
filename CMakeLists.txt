cmake_minimum_required(VERSION 3.5)
project(SGuitar)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/CPM.cmake)
CPMAddPackage("gh:nlohmann/json@3.11.3")
CPMAddPackage("gh:SRombauts/SQLiteCpp#3.3.2")
CPMAddPackage("gh:fmtlib/fmt#11.1.4")
CPMAddPackage("gh:doctest/doctest@2.4.11")

file(GLOB SOURCE_FILES "src/*.cpp")
file(GLOB GENERATED_CPP "generated-src/cpp/*.cpp")
file(GLOB GENERATED_OBJC "generated-src/objc/*.mm")
file(GLOB GENERATED_OBJC_CPP "generated-src/objc-cpp/*.mm")
file(GLOB GENERATED_JNI "generated-src/jni/*.cpp")
file(GLOB GENERATED_WASM "generated-src/wasm/*.cpp")
file(GLOB TEST_SOURCE_FILES "tests/src/*.cpp")
file(GLOB DJINNI_CPP "djinni/support-lib/cpp/*.cpp")
file(GLOB DJINNI_OBJC "djinni/support-lib/objc/*.mm")
file(GLOB DJINNI_JNI "djinni/support-lib/jni/*.cpp")
file(GLOB DJINNI_WASM "djinni/support-lib/wasm/*.cpp")
file(GLOB FRAMEWORK_INCLUDE "framework-include/*.h")
file(GLOB DJINNI_OBJC_HEADER "generated-src/objc/*.h")
set(FRAMEWORK_PUBLIC_HEADER
        ${DJINNI_OBJC_HEADER}
        ${FRAMEWORK_INCLUDE}
)
file(GLOB DJINNI_IDL "idl/*.djinni")

include_directories(PUBLIC
        "generated-src/cpp"
        "generated-src/objc"
        "generated-src/objc-cpp"
        "djinni/support-lib"
        "djinni/support-lib/cpp"
        "djinni/support-lib/objc"
        "djinni/support-lib/jni"
        "djinni/support-lib/wasm"
        "framework-include"
        "src"
)

if (EMSCRIPTEN)
    message(STATUS "Creating WebAssembly...")
    add_executable(SGuitar
            ${SOURCE_FILES}
            ${GENERATED_CPP}
            ${GENERATED_WASM}
            ${DJINNI_WASM}
    )
    set_target_properties(SGuitar PROPERTIES COMPILE_FLAGS "--no-entry -o SGuitar.js")
    set_target_properties(SGuitar PROPERTIES LINK_FLAGS "--bind --no-entry -o SGuitar.js -s MODULARIZE=1")
elseif (ANDROID)
    message(STATUS "Creating Android shared library...")
    add_library(SGuitar SHARED
            ${SOURCE_FILES}
            ${GENERATED_CPP}
            ${GENERATED_JNI}
            ${DJINNI_CPP}
            ${DJINNI_JNI}
    )
    target_link_libraries(SGuitar android log)
elseif (IOS)
    message(STATUS "Creating iOS framework Xcode project...")
    enable_language(Swift)
    set(CMAKE_SYSTEM_NAME iOS)
    set(CMAKE_OSX_SYSROOT "iphoneos")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES)

    add_library(SGuitar SHARED
            ${SOURCE_FILES}
            ${GENERATED_CPP}
            ${GENERATED_OBJC}
            ${GENERATED_OBJC_CPP}
            ${DJINNI_CPP}
            ${DJINNI_OBJC}
            ${FRAMEWORK_INCLUDE}
            ${DJINNI_OBJC_HEADER}
    )
    set_target_properties(SGuitar PROPERTIES
            FRAMEWORK TRUE
            FRAMEWORK_VERSION C
            MACOSX_FRAMEWORK_IDENTIFIER com.steelsidekick.SGuitar
            MACOSX_FRAMEWORK_INFO_PLIST resources/Info.plist
            VERSION 16.4.0
            SOVERSION 1.0.0
            PUBLIC_HEADER "${FRAMEWORK_PUBLIC_HEADER}"
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
            XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.steelsidekick.SGuitar"
    )
else ()
    message(STATUS "Building static library...")
    add_library(SGuitar STATIC
            ${SOURCE_FILES}
            ${GENERATED_CPP}
    )
endif ()
target_link_libraries(SGuitar nlohmann_json SQLiteCpp fmt)

if (NOT EMSCRIPTEN AND NOT ANDROID)
    message(STATUS "Building unit tests...")
    add_executable(tests ${TEST_SOURCE_FILES})
    target_link_libraries(tests SGuitar doctest)
    enable_testing()
    add_test(
            NAME tests
            COMMAND $<TARGET_FILE:tests> ${PROJECT_SOURCE_DIR}/db/ddl.sql "${PROJECT_SOURCE_DIR}/import/Lap Steel" "${PROJECT_SOURCE_DIR}/import/Pedal Steel"
    )
endif ()
