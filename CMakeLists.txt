cmake_minimum_required(VERSION 3.29)
project(SGuitar)

include(FetchContent)

# doctest
FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)

# nlohmann_json
FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

# nlohmann_json
FetchContent_Declare(
        SQLiteCpp
        GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
        GIT_TAG 3.3.2
)
FetchContent_MakeAvailable(SQLiteCpp)

# fmt
FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 11.0.2
)
FetchContent_MakeAvailable(fmt)

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
        tests/src/test.cpp
        tests/src/TestScales.cpp
        tests/src/TestChords.cpp
        tests/src/TestDB.cpp
        tests/src/TestFactory.cpp
)

include_directories(PUBLIC "src/generated/cpp")

add_library(SGuitar STATIC ${SOURCE})
target_link_libraries(SGuitar PRIVATE nlohmann_json)
target_link_libraries(SGuitar PRIVATE fmt)
target_link_libraries(SGuitar PRIVATE SQLiteCpp)

add_executable(tests ${SOURCE} ${TEST_SOURCE})
target_link_libraries(tests PRIVATE fmt)
target_link_libraries(tests PRIVATE doctest)
target_link_libraries(tests PRIVATE nlohmann_json)
target_link_libraries(tests PRIVATE SQLiteCpp)
enable_testing()
add_test(
        NAME tests
        COMMAND $<TARGET_FILE:tests>
)
