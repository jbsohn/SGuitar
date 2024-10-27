cmake_minimum_required(VERSION 3.29)
project(SGuitar)

#set(CMAKE_SYSTEM_NAME iOS)
#set(CMAKE_OSX_SYSROOT "iphoneos")
#set(CMAKE_OSX_ARCHITECTURES "x86_64" "arm64")
#set(CMAKE_XCODE_ATTRIBUTE_SDKROOT "iphoneos")
#set(CMAKE_XCODE_ATTRIBUTE_ARCHS "x86_64" "arm64")

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
file(GLOB SOURCE_FILES "src/*.cpp")
file(GLOB GENERATED_CPP "generated-src/cpp/*.cpp")
file(GLOB GENERATED_OBJC "generated-src/objc/*.mm")
file(GLOB GENERATED_OBJC-CPP "generated-src/objc-cpp/*.mm")
file(GLOB TEST_SOURCE_FILES "tests/src/*.cpp")
file(GLOB HEADER_FILES
        "include/SGuitar.h"
        "generated-src/objc/*.h"
)
include_directories(PUBLIC
        "generated-src/cpp"
        "generated-src/objc"
        "generated-src/objc-cpp"
        "include"
)

add_library(SGuitar STATIC "${SOURCE_FILES}")
target_link_libraries(SGuitar PRIVATE nlohmann_json)
target_link_libraries(SGuitar PRIVATE fmt)
target_link_libraries(SGuitar PRIVATE SQLiteCpp)

add_executable(tests ${TEST_SOURCE_FILES})
target_link_libraries(tests PRIVATE fmt)
target_link_libraries(tests PRIVATE doctest)
target_link_libraries(tests PRIVATE nlohmann_json)
target_link_libraries(tests PRIVATE SQLiteCpp)
target_link_libraries(tests PRIVATE SGuitar)
enable_testing()
add_test(
        NAME tests
        COMMAND $<TARGET_FILE:tests>
)


#add_library(SGuitar SHARED
#        ${SOURCE_FILES}
#        ${GENERATED_CPP}
#        ${GENERATED_OBJC}
#        ${GENERATED_OBJC_CPP}
#        ${HEADER_FILES}
#)
#set_target_properties(SGuitar PROPERTIES
#       FRAMEWORK TRUE
#       FRAMEWORK_VERSION C
#       MACOSX_FRAMEWORK_IDENTIFIER com.steelsidekick.SGuitar
#       XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 15.0
#       PUBLIC_HEADER "${HEADER_FILES}"
#       XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym"
#)
#target_link_libraries(SGuitar PRIVATE nlohmann_json)
#target_link_libraries(SGuitar PRIVATE fmt)
#target_link_libraries(SGuitar PRIVATE SQLiteCpp)
