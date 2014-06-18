set(DEPNAME glfw)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../lib/*.c")

set(HEADERS GL/glfw.h)

if (WIN32)
    file(GLOB WIN32_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../lib/win32/*.c")
    list(APPEND SOURCES ${WIN32_SOURCES})
endif()

if (APPLE)
    file(GLOB COCOA_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../lib/cocoa/*.[c|m]")
    list(APPEND SOURCES ${COCOA_SOURCES})
endif()

include_directories(../include ../lib)

cegui_add_library(${DEPNAME} SOURCES NONE)

if (WIN32)
    include_directories("../lib/win32")

    set_target_properties(${DEPNAME} PROPERTIES
        DEFINE_SYMBOL GLFW_BUILD_DLL
        COMPILE_DEFINITIONS "")

    set_target_properties(${DEPNAME}_static PROPERTIES
        COMPILE_DEFINITIONS "")

    target_link_libraries(${DEPNAME} opengl32)
endif()

if (APPLE)
    include_directories("../lib/cocoa")

    set_target_properties(${DEPNAME} PROPERTIES
        COMPILE_DEFINITIONS ""
        LINK_FLAGS "-framework Cocoa -framework OpenGL")

    set_target_properties(${DEPNAME}_static PROPERTIES
        COMPILE_DEFINITIONS "")
endif()

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../include/${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../COPYING.txt"
                                                    "${CMAKE_BINARY_DIR}/dependencies/glfw-COPYTING.txt")

