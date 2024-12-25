# auto generate DJINNI generated-src by examining note.hpp
#add_custom_command(
#        OUTPUT "${PROJECT_SOURCE_DIR}/generated-src/cpp/note.hpp"
#        COMMAND "${CMAKE_COMMAND}" -DDJINNI_RUN=${PROJECT_SOURCE_DIR}/djinni/src/run -DDJINNI_GENERATED_SRC=${PROJECT_SOURCE_DIR}/generated-src -DDJINNI_IDL=${PROJECT_SOURCE_DIR}/idl/sguitar.djinni -P ${PROJECT_SOURCE_DIR}/scripts/run-djinni.cmake
#        COMMENT "regenerating DJINNI sources..."
#        DEPENDS "${DJINNI_IDL}"
#        VERBATIM
#)
#add_custom_target(
#        djinni ALL
#        DEPENDS "${PROJECT_SOURCE_DIR}/generated-src/cpp/note.hpp"
#        VERBATIM
#)
#set_source_files_properties("${PROJECT_SOURCE_DIR}/generated-src/cpp/note.hpp" PROPERTIES GENERATED TRUE)
