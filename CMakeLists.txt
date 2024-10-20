cmake_minimum_required(VERSION 3.29)
project(SGuitar)

find_package(doctest CONFIG REQUIRED)
find_package(SQLiteCpp CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(INCLUDE, src/generated/cpp)
set(SOURCE
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
        src/implemented/factory/SGuitarFactory.cpp
)
set(TEST_SOURCE
        ${SOURCE}
        src/tests/test.cpp
        src/tests/TestScales.cpp
        src/tests/TestChords.cpp
        src/tests/TestDB.cpp
        src/tests/TestFactory.cpp
)

include_directories(PUBLIC "src/generated/cpp")

add_executable(SGuitarTest ${TEST_SOURCE})

target_link_libraries(SGuitarTest PRIVATE doctest::doctest)
target_link_libraries(SGuitarTest PRIVATE SQLiteCpp)
target_link_libraries(SGuitarTest PRIVATE nlohmann_json::nlohmann_json)

enable_testing()
add_test(
    NAME SGuitarTest
    COMMAND $<TARGET_FILE:SGuitarTest>
)

add_library (SGuitar SHARED ${SOURCE})
target_link_libraries(SGuitar ${FOUNDATION_LIBRARY})
target_compile_definitions(SGuitar PUBLIC IS_BUILDING_SHARED)
target_link_libraries(SGuitar PRIVATE doctest::doctest)
target_link_libraries(SGuitar PRIVATE SQLiteCpp)
target_link_libraries(SGuitar PRIVATE nlohmann_json::nlohmann_json)
