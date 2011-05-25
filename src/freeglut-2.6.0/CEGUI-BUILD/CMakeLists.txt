set(DEPNAME freeglut)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../src/*.c")

include_directories(
    ../src
    ../include)

cegui_add_library(${DEPNAME} SOURCES NONE)

if (WIN32)
    target_link_libraries(freeglut OpenGL32 winmm)
endif()

if (WIN32)
set_target_properties(${DEPNAME} PROPERTIES
    DEFINE_SYMBOL FREEGLUT_EXPORTS)
endif()

set_target_properties(${DEPNAME}_static PROPERTIES
    COMPILE_DEFINITIONS FREEGLUT_STATIC)

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/../include/GL"
                                                   "${CMAKE_BINARY_DIR}/dependencies/include/GL")

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../COPYING"
                                                    "${CMAKE_BINARY_DIR}/dependencies/freeglut-license.txt")

