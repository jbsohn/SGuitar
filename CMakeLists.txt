cmake_minimum_required(VERSION 3.29)
project(SGuitar)

set(CMAKE_CXX_STANDARD 20)

include_directories(PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/cpp/generated/cpp")
add_executable(
        SGuitarTest
        cpp/implemented/ChordImpl.cpp
        cpp/implemented/GuitarAdjustmentImpl.cpp
        cpp/implemented/GuitarImpl.cpp
        cpp/implemented/GuitarStringImpl.cpp
        cpp/implemented/NoteImpl.cpp
        cpp/implemented/ScaleImpl.cpp
        cpp/implemented/StringAdjustmentImpl.cpp
        tests/Test.cpp
)
enable_testing()
add_test(
        NAME SGuitarTest
        COMMAND $<TARGET_FILE:SGuitarTest>
)