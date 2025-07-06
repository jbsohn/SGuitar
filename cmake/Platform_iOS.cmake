message(STATUS "Creating iOS framework Xcode project...")
enable_language(Swift)
set(CMAKE_SYSTEM_NAME iOS)
set(CMAKE_OSX_SYSROOT "iphoneos")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES)
set(CMAKE_XCODE_ATTRIBUTE_BUILD_LIBRARY_FOR_DISTRIBUTION "YES")

add_library(SGuitar SHARED
        ${SOURCE_FILES}
        ${GENERATED_CPP}
        ${GENERATED_OBJC}
        ${GENERATED_OBJC_CPP}
        ${DJINNI_CPP}
        ${DJINNI_OBJC}
        ${FRAMEWORK_INCLUDE}
        ${DJINNI_OBJC_HEADER}
)
set_target_properties(SGuitar PROPERTIES
        FRAMEWORK TRUE
        FRAMEWORK_VERSION A
        MACOSX_FRAMEWORK_IDENTIFIER com.steelsidekick.SGuitar
        MACOSX_FRAMEWORK_INFO_PLIST ${PROJECT_SOURCE_DIR}/resources/Info.plist
        VERSION 1.0.0
        SOVERSION 1.0.0
        PUBLIC_HEADER "${FRAMEWORK_PUBLIC_HEADER}"
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Apple Development"
        XCODE_ATTRIBUTE_DEFINES_MODULE "YES"
        XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.steelsidekick.SGuitar"
        MACOSX_RPATH TRUE
        XCODE_ATTRIBUTE_SKIP_INSTALL "YES"
)
target_include_directories(SGuitar PUBLIC
        ${PROJECT_SOURCE_DIR}/generated-src/cpp
        ${PROJECT_SOURCE_DIR}/generated-src/objc
        ${PROJECT_SOURCE_DIR}/generated-src/objc-cpp
        ${PROJECT_SOURCE_DIR}/djinni/support-lib
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/cpp
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/objc
        ${PROJECT_SOURCE_DIR}/framework-include
        ${PROJECT_SOURCE_DIR}/src
)
target_link_libraries(SGuitar nlohmann_json SQLiteCpp fmt)