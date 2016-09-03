set(DEPNAME tinyxml2)

set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../tinyxml2.cpp")

set(HEADERS tinyxml2.h)

include_directories(../)

cegui_add_library(${DEPNAME} SOURCES NONE)

set_target_properties(${DEPNAME} PROPERTIES
	COMPILE_DEFINITIONS "TINYXML2_EXPORT")

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../readme.md"
                                                    "${CMAKE_BINARY_DIR}/dependencies/tinyxml2-README.txt")

