#
# Tests
#
message(STATUS "Building unit tests...")

file(GLOB SGUITAR_TESTS_SRC
        ${PROJECT_SOURCE_DIR}/tests/src/*.cpp
)

add_executable(SGuitarTests ${SGUITAR_TESTS_SRC})
target_link_libraries(SGuitarTests SGuitar doctest)

target_include_directories(SGuitarTests PRIVATE
        ${PROJECT_SOURCE_DIR}/tests/src
)

enable_testing()

add_test(
        NAME SGuitarTests
        COMMAND $<TARGET_FILE:SGuitarTests>
        ${PROJECT_SOURCE_DIR}/db/ddl.sql
        "${PROJECT_SOURCE_DIR}/import/Lap Steel"
        "${PROJECT_SOURCE_DIR}/import/Pedal Steel"
)