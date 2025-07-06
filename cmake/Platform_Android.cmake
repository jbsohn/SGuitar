#
# Android
#
message(STATUS "Creating Android shared library...")
add_library(SGuitar SHARED
        ${SOURCE_FILES}
        ${GENERATED_CPP}
        ${GENERATED_JNI}
        ${DJINNI_CPP}
        ${DJINNI_JNI}
)
target_include_directories(SGuitar PUBLIC
        ${PROJECT_SOURCE_DIR}/generated-src/cpp
        ${PROJECT_SOURCE_DIR}/djinni/support-lib
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/cpp
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/jni
        ${PROJECT_SOURCE_DIR}/src
)
target_link_libraries(SGuitar nlohmann_json SQLiteCpp fmt android log)
