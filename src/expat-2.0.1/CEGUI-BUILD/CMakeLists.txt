set(DEPNAME expat)

set(SOURCES ../lib/libexpat.def ../lib/xmlrole.c ../lib/xmltok.c ../lib/xmlparse.c)
set(HEADERS expat.h expat_external.h)

add_definitions(-DCOMPILED_FROM_DSP)

cegui_add_library(${DEPNAME} SOURCES NONE)


set_target_properties(${DEPNAME} PROPERTIES
    DEFINE_SYMBOL EXPAT_EXPORTS)

foreach(_H_FILE ${HEADERS})
add_custom_command(TARGET ${DEPNAME} POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../lib/${_H_FILE}"
                                         "${CMAKE_BINARY_DIR}/include/${_H_FILE}")
endforeach()
