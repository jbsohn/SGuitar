cmake_minimum_required(VERSION 3.29)
project(SGuitar)

find_package(doctest CONFIG REQUIRED)
find_package(SQLiteCpp CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)

include_directories(PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/generated/cpp")
add_executable(
        SGuitarTest
        src/implemented/HarmonizedScaleImpl.cpp
        src/implemented/ChordImpl.cpp
        src/implemented/GuitarAdjustmentImpl.cpp
        src/implemented/GuitarImpl.cpp
        src/implemented/GuitarStringImpl.cpp
        src/implemented/NoteImpl.cpp
        src/implemented/ScaleImpl.cpp
        src/implemented/StringAdjustmentImpl.cpp
        src/tests/test.cpp
        src/tests/TestScales.cpp
        src/tests/TestChords.cpp
        src/tests/TestDB.cpp
        src/implemented/SGuitarDBImpl.cpp
        src/implemented/ScaleDAOImpl.cpp
)
target_link_libraries(SGuitarTest PRIVATE doctest::doctest)
target_link_libraries(SGuitarTest PRIVATE SQLiteCpp)

enable_testing()
add_test(
        NAME SGuitarTest
        COMMAND $<TARGET_FILE:SGuitarTest>
)