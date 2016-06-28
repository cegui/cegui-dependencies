set(DEPNAME libexpat)

set(SOURCES ../lib/xmlrole.c ../lib/xmltok.c ../lib/xmlparse.c)
set(HEADERS expat.h expat_external.h)

if(WIN32)
    add_definitions(-DCOMPILED_FROM_DSP)
endif()

cegui_add_library(${DEPNAME} SOURCES NONE)

set_target_properties(${DEPNAME} PROPERTIES
    DEFINE_SYMBOL EXPAT_EXPORTS)

if (WIN32)
    if (MSVC)
        set_target_properties(${DEPNAME} PROPERTIES
            LINK_FLAGS_RELEASE "/DEF:\"${CMAKE_CURRENT_SOURCE_DIR}/../lib/libexpat.def\""
            LINK_FLAGS_DEBUG   "/DEF:\"${CMAKE_CURRENT_SOURCE_DIR}/../lib/libexpat${CMAKE_DEBUG_POSTFIX}.def\"")
    else()
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
            list(APPEND SOURCES ../lib/libexpat${CMAKE_DEBUG_POSTFIX}.def)
        else()
            list(APPEND SOURCES ../lib/libexpat.def)
        endif()
    endif()
else()
    set_target_properties(${DEPNAME} PROPERTIES
        COMPILE_DEFINITIONS HAVE_MEMMOVE)

    set_target_properties(${DEPNAME}_static PROPERTIES
        COMPILE_DEFINITIONS HAVE_MEMMOVE)
endif()

# In the case of libexpat, we need to remove any prefixes that get generated
# to prevent a double `lib` prefixing (e.g.: liblibexpat.(a|dll)) being generated.
# This is the case when compiling with gcc for example. Thus, we set no prefix
# for the dynamic and static libraries.

set_target_properties(${DEPNAME} PROPERTIES
    IMPORT_PREFIX ""
    PREFIX "")

set_target_properties(${DEPNAME}_static PROPERTIES
    PREFIX "")

foreach(_H_FILE ${HEADERS})
add_custom_command(TARGET ${DEPNAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../lib/${_H_FILE}"
                                         "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()


add_custom_command(TARGET ${DEPNAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../COPYING"
                                                    "${CMAKE_BINARY_DIR}/dependencies/expat-license.txt")
