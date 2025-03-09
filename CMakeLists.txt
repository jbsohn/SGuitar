cmake_minimum_required(VERSION 3.25.1)
project(SGuitar)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_CURRENT_SOURCE_DIR}/dependencies.cmake)

# doctest
FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)

file(GLOB SOURCE_FILES "src/*.cpp")
file(GLOB GENERATED_CPP "generated-src/cpp/*.cpp")
file(GLOB GENERATED_OBJC "generated-src/objc/*.mm")
file(GLOB GENERATED_OBJC_CPP "generated-src/objc-cpp/*.cpp")
file(GLOB GENERATED_WASM "generated-src/wasm/*.cpp")
file(GLOB TEST_SOURCE_FILES "tests/src/*.cpp")
file(GLOB DJINNI_CPP "djinni/support-lib/cpp/*.cpp")
file(GLOB DJINNI_OBJC "djinni/support-lib/objc/*")
file(GLOB DJINNI_OBJC_HEADER "generated-src/objc/*.h")
file(GLOB DJINNI_WASM "djinni/support-lib/wasm/*.cpp")
file(GLOB DJINNI_IDL "idl/*")

include_directories(PUBLIC
        "generated-src/cpp"
        "generated-src/objc"
        "generated-src/objc-cpp"
        "djinni/support-lib"
        "djinni/support-lib/cpp"
        "djinni/support-lib/objc"
        "djinni/support-lib/wasm"
        "include"
)
include_directories(PRIVATE "src")

if(EMSCRIPTEN)
    message(STATUS "Building WebAssembly...")
    add_executable(SGuitar
            ${SOURCE_FILES}
            ${DJINNI_WASM}
            ${GENERATED_CPP}
            ${GENERATED_WASM}
    )
    set_target_properties(SGuitar PROPERTIES COMPILE_FLAGS "--no-entry -o SGuitar.js")
    set_target_properties(SGuitar PROPERTIES LINK_FLAGS    "--bind --no-entry -o SGuitar.js -s MODULARIZE=1")
else()
    message(STATUS "Building static library...")
    add_library(SGuitar STATIC
            ${SOURCE_FILES}
            ${GENERATED_CPP}
    )
endif()
target_link_libraries(SGuitar PRIVATE nlohmann_json)
target_link_libraries(SGuitar PRIVATE fmt)
target_link_libraries(SGuitar PRIVATE SQLiteCpp)

if(NOT EMSCRIPTEN)
    message(STATUS "Building unit tests...")
    add_executable(tests ${TEST_SOURCE_FILES})
    target_link_libraries(tests PRIVATE nlohmann_json)
    target_link_libraries(tests PRIVATE fmt)
    target_link_libraries(tests PRIVATE SQLiteCpp)
    target_link_libraries(tests PRIVATE doctest)
    target_link_libraries(tests PRIVATE SGuitar)
    enable_testing()
    add_test(
            NAME tests
            COMMAND $<TARGET_FILE:tests>
    )
endif()
