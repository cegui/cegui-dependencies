set(DEPNAME minizip)

set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../unzip.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/../zip.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/../ioapi.c")
if (WIN32)
    list (APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../iowin32.c")
endif()

set(HEADERS zip.h unzip.h ioapi.h)

include_directories(../ ${CMAKE_BINARY_DIR}/dependencies/include)

cegui_add_library(${DEPNAME} SOURCES NONE)

set_target_properties(${DEPNAME} PROPERTIES
    COMPILE_DEFINITIONS USE_FILE32API)

set_target_properties(${DEPNAME}_static PROPERTIES
    COMPILE_DEFINITIONS "MINIZIP_STATIC;USE_FILE32API")

target_link_libraries(${DEPNAME} zlib)
add_dependencies(${DEPNAME}_static zlib)

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/dependencies/include/minizip/${_H_FILE}")
endforeach()

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../license"
                                                    "${CMAKE_BINARY_DIR}/dependencies/minizip-license.txt")

