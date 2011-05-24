set(DEPNAME libpng)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../png*.c")
list(APPEND SOURCES ../scripts/pngwin.def)
list(REMOVE_ITEM SOURCES ../pnggccrd.c ../pngvcrd.c ../pngtest.c)

set(HEADERS png.h pngconf.h)

include_directories(../ ${CMAKE_BINARY_DIR}/dependencies/include)

cegui_add_library(${DEPNAME} SOURCES NONE)

set_target_properties(${DEPNAME} PROPERTIES
    COMPILE_DEFINITIONS_DEBUG "PNG_DEBUG=1"
    COMPILE_DEFINITIONS "PNG_BUILD_DLL;ZLIB_DLL;PNG_NO_MMX_CODE")

target_link_libraries(${DEPNAME} zlib)


set_target_properties(${DEPNAME}_static PROPERTIES
    COMPILE_DEFINITIONS_DEBUG "PNG_DEBUG=1"
    COMPILE_DEFINITIONS PNG_NO_MMX_CODE)

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()


add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE"
                                                    "${CMAKE_BINARY_DIR}/dependencies/libpng-license.txt")

