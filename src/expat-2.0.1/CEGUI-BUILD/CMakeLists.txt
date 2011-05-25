set(DEPNAME expat)

set(SOURCES ../lib/libexpat.def ../lib/xmlrole.c ../lib/xmltok.c ../lib/xmlparse.c)
set(HEADERS expat.h expat_external.h)

if(WIN32)
    add_definitions(-DCOMPILED_FROM_DSP)
endif()

cegui_add_library(${DEPNAME} SOURCES NONE)

set_target_properties(${DEPNAME} PROPERTIES
    DEFINE_SYMBOL EXPAT_EXPORTS)

if (NOT WIN32)
    set_target_properties(${DEPNAME} PROPERTIES
        COMPILE_DEFINITIONS HAVE_MEMMOVE)

    set_target_properties(${DEPNAME}_static PROPERTIES
        COMPILE_DEFINITIONS HAVE_MEMMOVE)

endif()

foreach(_H_FILE ${HEADERS})
add_custom_command(TARGET ${DEPNAME} POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../lib/${_H_FILE}"
                                         "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()


add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../COPYING"
                                                    "${CMAKE_BINARY_DIR}/dependencies/expat-license.txt")
