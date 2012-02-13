set(DEPNAME tinyxml)

set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../tinystr.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/../tinyxml.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/../tinyxmlerror.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/../tinyxmlparser.cpp")

set(HEADERS tinystr.h tinyxml.h)

include_directories(../)

cegui_add_library(${DEPNAME} SOURCES NONE)

set_target_properties(${DEPNAME}_static PROPERTIES
    COMPILE_DEFINITIONS TINYXML_STATIC)

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../license"
                                                    "${CMAKE_BINARY_DIR}/dependencies/tinyxml-license.txt")

