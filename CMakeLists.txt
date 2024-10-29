cmake_minimum_required(VERSION 3.29)
project(SGuitar)

#enable_language(Swift)
#set(CMAKE_SYSTEM_NAME iOS)
#set(CMAKE_OSX_SYSROOT "iphoneos")
#set(CMAKE_OSX_ARCHITECTURES "x86_64" "arm64")
#set(CMAKE_XCODE_ATTRIBUTE_SDKROOT "iphoneos")
#set(CMAKE_XCODE_ATTRIBUTE_ARCHS "x86_64" "arm64")
#set(CMAKE_XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES)

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

# SQLiteCpp
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
file(GLOB SOURCE_FILES "src/*")
file(GLOB GENERATED_CPP "generated-src/cpp/*")
file(GLOB GENERATED_OBJC "generated-src/objc/*")
file(GLOB GENERATED_OBJC_CPP "generated-src/objc-cpp/*")
file(GLOB TEST_SOURCE_FILES "tests/src/*")
file(GLOB DJINNI_CPP "djinni/support-lib/cpp/*")
file(GLOB DJINNI_OBJC "djinni/support-lib/objc/*")
file(GLOB FRAMEWORK_INCLUDE "framework-include/*")
file(GLOB DJINNI_OBJC_HEADER "generated-src/objc/*.h")
set(FRAMEWORK_PUBLIC_HEADER
        ${FRAMEWORK_INCLUDE}
        ${DJINNI_OBJC_HEADER}
)
include_directories(PUBLIC
        "generated-src/cpp"
        "generated-src/objc"
        "generated-src/objc-cpp"
        "djinni/support-lib"
        "djinni/support-lib/cpp"
        "djinni/support-lib/objc"
        "include"
        "framework-include"
)

# current platform unit tests
add_library(SGuitar STATIC
        ${SOURCE_FILES}
        ${GENERATED_CPP}
)
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

# iOS Framework
#add_library(SGuitar SHARED
#        ${SOURCE_FILES}
#        ${GENERATED_CPP}
#        ${GENERATED_OBJC}
#        ${GENERATED_OBJC_CPP}
#        ${DJINNI_CPP}
#        ${DJINNI_OBJC}
#        ${FRAMEWORK_INCLUDE}
#)
#set_target_properties(SGuitar PROPERTIES
#        FRAMEWORK TRUE
#        FRAMEWORK_VERSION A
#        MACOSX_FRAMEWORK_IDENTIFIER com.steelsidekick.SGuitar
#        MACOSX_FRAMEWORK_INFO_PLIST ${PROJECT_SOURCE_DIR}/resources/Info.plist
#        VERSION 1.0.0
#        SOVERSION 1.0.0
#        PUBLIC_HEADER "${FRAMEWORK_PUBLIC_HEADER}"
#        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
##        XCODE_ATTRIBUTE_MODULEMAP_FILE "resources/module.modulemap"
#        XCODE_ATTRIBUTE_DEFINES_MODULE "YES"
#)
#target_link_libraries(SGuitar PRIVATE nlohmann_json)
#target_link_libraries(SGuitar PRIVATE fmt)
#target_link_libraries(SGuitar PRIVATE SQLiteCpp)
