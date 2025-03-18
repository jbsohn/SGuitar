cmake_minimum_required(VERSION 3.25.1)
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
file(GLOB GENERATED_OBJC_CPP "generated-src/objc-cpp/*.cpp")
file(GLOB GENERATED_JNI "generated-src/jni/*.cpp")
file(GLOB GENERATED_WASM "generated-src/wasm/*.cpp")
file(GLOB TEST_SOURCE_FILES "tests/src/*.cpp")
file(GLOB DJINNI_CPP "djinni/support-lib/cpp/*.cpp")
file(GLOB DJINNI_OBJC "djinni/support-lib/objc/*.mm")
file(GLOB DJINNI_JNI "djinni/support-lib/jni/*.cpp")
file(GLOB DJINNI_WASM "djinni/support-lib/wasm/*.cpp")
file(GLOB DJINNI_IDL "idl/*.djinni")

include_directories(PRIVATE
        "generated-src/cpp"
        "generated-src/objc"
        "generated-src/objc-cpp"
        "djinni/support-lib"
        "djinni/support-lib/cpp"
        "djinni/support-lib/objc"
        "djinni/support-lib/jni"
        "djinni/support-lib/wasm"
        "src"
)

if (EMSCRIPTEN)
    message(STATUS "Building WebAssembly...")
    add_executable(SGuitar
            ${SOURCE_FILES}
            ${GENERATED_CPP}
            ${GENERATED_WASM}
            ${DJINNI_WASM}
    )
    set_target_properties(SGuitar PROPERTIES COMPILE_FLAGS "--no-entry -o SGuitar.js")
    set_target_properties(SGuitar PROPERTIES LINK_FLAGS "--bind --no-entry -o SGuitar.js -s MODULARIZE=1")
elseif (ANDROID)
    message(STATUS "Building Android shared library...")
    add_library(SGuitar SHARED
            ${SOURCE_FILES}
            ${GENERATED_CPP}
            ${GENERATED_JNI}
            ${DJINNI_CPP}
            ${DJINNI_JNI}
    )
    target_link_libraries(SGuitar android log)
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
            COMMAND $<TARGET_FILE:tests>
    )
endif ()
