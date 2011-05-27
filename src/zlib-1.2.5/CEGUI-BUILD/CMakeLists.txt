set(DEPNAME zlib)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../*.c")
list(REMOVE_ITEM SOURCES ../example.c ../minigzip.c)

set(HEADERS zlib.h zconf.h)

include_directories("../")

cegui_add_library(${DEPNAME} SOURCES NONE)

set_target_properties(${DEPNAME} PROPERTIES
    DEFINE_SYMBOL ZLIB_DLL)

if (APPLE)
    set_target_properties(${DEPNAME} PROPERTIES
        COMPILE_DEFINITIONS Z_HAVE_UNISTD_H)

    set_target_properties(${DEPNAME}_static PROPERTIES
        COMPILE_DEFINITIONS Z_HAVE_UNISTD_H)
endif()


foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../README"
                                                    "${CMAKE_BINARY_DIR}/dependencies/zlib-README.txt")

