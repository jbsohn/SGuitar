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

file(GLOB SOURCE_FILES "src/*")
file(GLOB GENERATED_CPP "generated-src/cpp/*")
file(GLOB GENERATED_OBJC "generated-src/objc/*")
file(GLOB GENERATED_OBJC_CPP "generated-src/objc-cpp/*")
file(GLOB TEST_SOURCE_FILES "tests/src/*")
file(GLOB DJINNI_CPP "djinni/support-lib/cpp/*")
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
        "include"
)
include_directories(PRIVATE "src")

message(STATUS "Building unit tests...")
add_library(SGuitar STATIC
        ${SOURCE_FILES}
        ${DJINNI_WASM}
        ${GENERATED_CPP}
)
target_link_libraries(SGuitar PRIVATE nlohmann_json)
#target_link_libraries(SGuitar PRIVATE fmt)
target_link_libraries(SGuitar PRIVATE SQLiteCpp)

#add_executable(tests ${TEST_SOURCE_FILES})
#target_link_libraries(tests PRIVATE nlohmann_json)
##target_link_libraries(tests PRIVATE fmt)
#target_link_libraries(tests PRIVATE SQLiteCpp)
#target_link_libraries(tests PRIVATE doctest)
#target_link_libraries(tests PRIVATE SGuitar)
#enable_testing()
#add_test(
#        NAME tests
#        COMMAND $<TARGET_FILE:tests>
#)
