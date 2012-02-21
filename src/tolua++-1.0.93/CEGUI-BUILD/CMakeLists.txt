set(DEPNAME toluapp)


file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../src/lib/*.c")
set(HEADERS tolua++.h)

include_directories(../include ../src/lib ${CMAKE_BINARY_DIR}/dependencies/include)

cegui_add_library(${DEPNAME} SOURCES NONE)

set_target_properties(${DEPNAME}_static PROPERTIES
    COMPILE_DEFINITIONS "TOLUA_STATIC;LUA_STATIC")

target_link_libraries(${DEPNAME} lua)

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../include/${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../COPYRIGHT"
                                                    "${CMAKE_BINARY_DIR}/dependencies/tolua++-license.txt")

