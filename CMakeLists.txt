cmake_minimum_required(VERSION 3.29)
project(SGuitar)

set(CMAKE_CXX_STANDARD 20)

include_directories(PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/generated/cpp")

add_executable(
        SGuitar
        implemented/ChordImpl.cpp
        implemented/GuitarAdjustmentImpl.cpp
        implemented/GuitarImpl.cpp
        implemented/GuitarStringImpl.cpp
        implemented/NoteImpl.cpp
        implemented/ScaleImpl.cpp
        implemented/StringAdjustmentImpl.cpp
        src/main.cpp
)

add_executable(
        SGuitarTest
        implemented/ChordImpl.cpp
        implemented/GuitarAdjustmentImpl.cpp
        implemented/GuitarImpl.cpp
        implemented/GuitarStringImpl.cpp
        implemented/NoteImpl.cpp
        implemented/ScaleImpl.cpp
        implemented/StringAdjustmentImpl.cpp
        tests/Test.cpp
)
enable_testing()
add_test(
        NAME SGuitarTest
        COMMAND $<TARGET_FILE:SGuitarTest>
)