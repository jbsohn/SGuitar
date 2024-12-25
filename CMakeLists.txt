cmake_minimum_required(VERSION 3.29)
project(SGuitar)

if (${TARGET} MATCHES "iOS")
    message(STATUS "Configuring build for iOS...")
    enable_language(Swift)
    set(CMAKE_SYSTEM_NAME iOS)
    set(CMAKE_OSX_SYSROOT "iphoneos")
    set(CMAKE_OSX_ARCHITECTURES "x86_64" "arm64")
    set(CMAKE_XCODE_ATTRIBUTE_SDKROOT "iphoneos")
    set(CMAKE_XCODE_ATTRIBUTE_ARCHS "x86_64" "arm64")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES)
    set(CMAKE_XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.steelsidekick.SGuitar")
endif ()

include(${CMAKE_CURRENT_SOURCE_DIR}/dependencies.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/defines.cmake)

if (${TARGET} MATCHES "iOS")
    message(STATUS "Building framework for iOS...")
    add_library(SGuitar SHARED
            ${SOURCE_FILES}
            ${GENERATED_CPP}
            ${GENERATED_OBJC}
            ${GENERATED_OBJC_CPP}
            ${DJINNI_CPP}
            ${DJINNI_OBJC}
            ${FRAMEWORK_INCLUDE}
    )
    set_target_properties(SGuitar PROPERTIES
            FRAMEWORK TRUE
            FRAMEWORK_VERSION A
            MACOSX_FRAMEWORK_IDENTIFIER com.steelsidekick.SGuitar
            MACOSX_FRAMEWORK_INFO_PLIST ${PROJECT_SOURCE_DIR}/resources/Info.plist
            VERSION 1.0.0
            SOVERSION 1.0.0
            PUBLIC_HEADER "${FRAMEWORK_PUBLIC_HEADER}"
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
            XCODE_ATTRIBUTE_DEFINES_MODULE "YES"
            XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
    )
    target_link_libraries(SGuitar PRIVATE nlohmann_json)
    target_link_libraries(SGuitar PRIVATE fmt)
    target_link_libraries(SGuitar PRIVATE SQLiteCpp)
else ()
    message(STATUS "Building unit tests for current native platform...")
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
endif ()
