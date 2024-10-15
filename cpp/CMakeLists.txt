cmake_minimum_required(VERSION 3.29)
project(SGuitar)

find_package(doctest CONFIG REQUIRED)
find_package(SQLiteCpp CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)

include_directories(PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/generated/cpp")
include_directories(PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/factory")

add_executable(
        SGuitarTest
        src/implemented/objects/HarmonizedScaleImpl.cpp
        src/implemented/objects/ChordImpl.cpp
        src/implemented/objects/GuitarAdjustmentImpl.cpp
        src/implemented/objects/GuitarImpl.cpp
        src/implemented/objects/GuitarStringImpl.cpp
        src/implemented/objects/NoteImpl.cpp
        src/implemented/objects/ScaleImpl.cpp
        src/implemented/objects/StringAdjustmentImpl.cpp
        src/implemented/dao/SGuitarDatabaseImpl.cpp
        src/implemented/dao/ScaleDAOImpl.cpp
        src/implemented/dao/ChordDAOImpl.cpp
        src/implemented/dao/GuitarDAOImpl.cpp
        src/factory/SGuitarFactory.cpp
        src/tests/test.cpp
        src/tests/TestScales.cpp
        src/tests/TestChords.cpp
        src/tests/TestDB.cpp
        src/tests/TestFactory.cpp
)

target_link_libraries(SGuitarTest PRIVATE doctest::doctest)
target_link_libraries(SGuitarTest PRIVATE SQLiteCpp)
target_link_libraries(SGuitarTest PRIVATE nlohmann_json::nlohmann_json)

enable_testing()
add_test(
        NAME SGuitarTest
        COMMAND $<TARGET_FILE:SGuitarTest>
)