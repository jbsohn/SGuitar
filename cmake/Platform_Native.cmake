message(STATUS "Building static library...")
add_library(SGuitar STATIC
        ${SOURCE_FILES}
        ${GENERATED_CPP}
)
target_include_directories(SGuitar PUBLIC
        ${PROJECT_SOURCE_DIR}/generated-src/cpp
        ${PROJECT_SOURCE_DIR}/generated-src/objc
        ${PROJECT_SOURCE_DIR}/generated-src/objc-cpp
        ${PROJECT_SOURCE_DIR}/djinni/support-lib
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/cpp
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/objc
        ${PROJECT_SOURCE_DIR}/src
)
target_link_libraries(SGuitar nlohmann_json SQLiteCpp fmt)
