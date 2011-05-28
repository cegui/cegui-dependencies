set(DEPNAME libpng)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../png*.c")
list(REMOVE_ITEM SOURCES ../pnggccrd.c ../pngvcrd.c ../pngtest.c)

if (WIN32)
    list(APPEND SOURCES ../scripts/pngwin.def)
endif()

set(HEADERS png.h pngconf.h)

include_directories(../ ${CMAKE_BINARY_DIR}/dependencies/include)

cegui_add_library(${DEPNAME} SOURCES NONE)

if (WIN32)
    set_target_properties(${DEPNAME} PROPERTIES
        DEFINE_SYMBOL "PNG_BUILD_DLL"
        COMPILE_DEFINITIONS "ZLIB_DLL")
endif()

set_property(TARGET ${DEPNAME} APPEND PROPERTY
    COMPILE_DEFINITIONS "PNG_NO_MMX_CODE")

set_target_properties(${DEPNAME} PROPERTIES
    COMPILE_DEFINITIONS_DEBUG "PNG_DEBUG=1")

target_link_libraries(${DEPNAME} zlib)

# this is needed because the headers for zlib are only copied as part of
# the shared build
add_dependencies(${DEPNAME}_static zlib)

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

