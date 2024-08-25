cmake_minimum_required(VERSION 3.29)
project(SGuitar)

set(CMAKE_CXX_STANDARD 20)

include_directories(PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/generated/cpp")

add_executable(SGuitar main.cpp
        implemented/ChordImpl.cpp
        implemented/GuitarAdjustmentImpl.cpp
        implemented/GuitarImpl.cpp
        implemented/GuitarStringImpl.cpp
        implemented/NoteImpl.cpp
        implemented/ScaleImpl.cpp
        implemented/StringAdjustmentImpl.cpp
        )
