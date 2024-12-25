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
file(GLOB DJINNI_IDL "idl/*")
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
