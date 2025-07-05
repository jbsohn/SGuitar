cmake_minimum_required(VERSION 3.25)
project(SGuitar)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
include(cmake/CPM.cmake)
CPMAddPackage("gh:nlohmann/json@3.11.3")
CPMAddPackage("gh:SRombauts/SQLiteCpp#3.3.2")
CPMAddPackage("gh:fmtlib/fmt#11.1.4")
CPMAddPackage("gh:doctest/doctest@2.4.11")

# Source files
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
file(GLOB DJINNI_IDL "idl/*.djinni")

set(FRAMEWORK_PUBLIC_HEADER
        ${DJINNI_OBJC_HEADER}
        ${FRAMEWORK_INCLUDE}
)

# Platform-specific build
if (EMSCRIPTEN)
    message(STATUS "Creating WebAssembly...")
    add_executable(SGuitar
            ${SOURCE_FILES}
            ${GENERATED_CPP}
            ${GENERATED_WASM}
            ${DJINNI_WASM}
    )
    set_target_properties(SGuitar PROPERTIES
            COMPILE_FLAGS "--no-entry -o SGuitar.js"
            LINK_FLAGS "--bind --no-entry -o SGuitar.js -s MODULARIZE=1"
    )
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
            FRAMEWORK_VERSION A
            MACOSX_FRAMEWORK_IDENTIFIER com.steelsidekick.SGuitar
            MACOSX_FRAMEWORK_INFO_PLIST ${PROJECT_SOURCE_DIR}/resources/Info.plist
            VERSION 1.0.0
            SOVERSION 1.0.0
            PUBLIC_HEADER "${FRAMEWORK_PUBLIC_HEADER}"
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Apple Development"
            XCODE_ATTRIBUTE_DEFINES_MODULE "YES"
            XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.steelsidekick.SGuitar"
            MACOSX_RPATH TRUE
            XCODE_ATTRIBUTE_SKIP_INSTALL "YES"
    )
else()
    message(STATUS "Building static library...")
    add_library(SGuitar STATIC
            ${SOURCE_FILES}
            ${GENERATED_CPP}
    )
endif()

target_include_directories(SGuitar PUBLIC
        ${PROJECT_SOURCE_DIR}/generated-src/cpp
        ${PROJECT_SOURCE_DIR}/generated-src/objc
        ${PROJECT_SOURCE_DIR}/generated-src/objc-cpp
        ${PROJECT_SOURCE_DIR}/djinni/support-lib
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/cpp
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/objc
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/jni
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/wasm
        ${PROJECT_SOURCE_DIR}/framework-include
        ${PROJECT_SOURCE_DIR}/src
)
target_link_libraries(SGuitar nlohmann_json SQLiteCpp fmt)

# Unit tests
if (NOT EMSCRIPTEN AND NOT ANDROID AND NOT IOS)
    message(STATUS "Building unit tests...")

    file(GLOB SGUITAR_TESTS_SRC
            ${PROJECT_SOURCE_DIR}/tests/src/*.cpp
    )

    add_executable(SGuitarTests ${SGUITAR_TESTS_SRC})
    target_link_libraries(SGuitarTests SGuitar doctest)

    target_include_directories(SGuitarTests PRIVATE
            ${PROJECT_SOURCE_DIR}/tests/src
    )

    enable_testing()

    add_test(
            NAME SGuitarTests
            COMMAND $<TARGET_FILE:SGuitarTests>
            ${PROJECT_SOURCE_DIR}/db/ddl.sql
            "${PROJECT_SOURCE_DIR}/import/Lap Steel"
            "${PROJECT_SOURCE_DIR}/import/Pedal Steel"
    )
endif()
