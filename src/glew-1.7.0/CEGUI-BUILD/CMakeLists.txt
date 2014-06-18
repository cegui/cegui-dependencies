set(DEPNAME glew)

set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../src/glew.c")

set(HEADERS GL/glew.h GL/glxew.h GL/wglew.h)

include_directories(../include ${CMAKE_BINARY_DIR}/dependencies/include)

cegui_add_library(${DEPNAME} SOURCES NONE)

if (WIN32)
    set_target_properties(${DEPNAME} PROPERTIES
        DEFINE_SYMBOL GLEW_BUILD)

    target_link_libraries(${DEPNAME} opengl32)
endif()

if (APPLE)
    set_target_properties(${DEPNAME} PROPERTIES
        LINK_FLAGS "-framework OpenGL")
endif()

set_target_properties(${DEPNAME}_static PROPERTIES
    COMPILE_DEFINITIONS GLEW_STATIC)

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../include/${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE.txt"
                                                    "${CMAKE_BINARY_DIR}/dependencies/glew-license.txt")

