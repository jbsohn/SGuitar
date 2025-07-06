message(STATUS "Creating WebAssembly...")
add_executable(SGuitar
        ${SOURCE_FILES}
        ${GENERATED_CPP}
        ${GENERATED_WASM}
        ${DJINNI_WASM}
)
target_compile_options(SGuitar PRIVATE "--no-entry -o SGuitar.js")
target_link_options(SGuitar PRIVATE "--bind --no-entry -o SGuitar.js -s MODULARIZE=1")
target_include_directories(SGuitar PUBLIC
        ${PROJECT_SOURCE_DIR}/generated-src/cpp
        ${PROJECT_SOURCE_DIR}/djinni/support-lib
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/cpp
        ${PROJECT_SOURCE_DIR}/djinni/support-lib/wasm
        ${PROJECT_SOURCE_DIR}/framework-include
        ${PROJECT_SOURCE_DIR}/src
)
target_link_libraries(SGuitar nlohmann_json SQLiteCpp fmt)