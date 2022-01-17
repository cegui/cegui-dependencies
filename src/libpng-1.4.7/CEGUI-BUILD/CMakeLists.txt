set(DEPNAME libpng)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../png*.c")
list(REMOVE_ITEM SOURCES ../pnggccrd.c ../pngvcrd.c ../pngtest.c)

set(HEADERS ../png.h ../pngconf.h)

include_directories(../ ${CMAKE_BINARY_DIR}/dependencies/include)

foreach(_H_FILE ${HEADERS})
	# From CMake 3.20:
	#cmake_path(RELATIVE_PATH ${_H_FILE} "${CMAKE_CURRENT_SOURCE_DIR}/../src")
	get_filename_component(_H_FILE "${_H_FILE}" ABSOLUTE)
	file(RELATIVE_PATH _H_FILE "${CMAKE_CURRENT_SOURCE_DIR}/.." ${_H_FILE})
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}" COPYONLY)
endforeach()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE" "${CMAKE_BINARY_DIR}/dependencies/libpng-license.txt" COPYONLY)

cegui_add_library(${DEPNAME} SOURCES NONE)

if (WIN32)
    set_target_properties(${DEPNAME} PROPERTIES
        DEFINE_SYMBOL "PNG_BUILD_DLL"
        COMPILE_DEFINITIONS "ZLIB_DLL")

    if (MSVC)
        set_target_properties(${DEPNAME} PROPERTIES
            LINK_FLAGS_RELEASE "/DEF:\"${CMAKE_CURRENT_SOURCE_DIR}/../scripts/pngwin.def\""
            LINK_FLAGS_DEBUG   "/DEF:\"${CMAKE_CURRENT_SOURCE_DIR}/../scripts/pngwin${CMAKE_DEBUG_POSTFIX}.def\"")
    else()
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
            list(APPEND SOURCES ../scripts/pngwin${CMAKE_DEBUG_POSTFIX}.def)
        else()
            list(APPEND SOURCES ../scripts/pngwin.def)
        endif()
    endif()
endif()

set_property(TARGET ${DEPNAME} APPEND PROPERTY
    COMPILE_DEFINITIONS "PNG_NO_MMX_CODE")

# In the case of libpng, we need to remove any prefixes that get generated
# to prevent a double `lib` prefixing (e.g.: liblibpng.(a|dll)) being generated.
# This is the case when compiling with gcc for example. Thus, we set no prefix
# for the dynamic and static libraries.

set(TARGET_COMPILE_FLAGS
    $<$<CONFIG:Debug>:PNG_DEBUG=1>
)

set_target_properties(${DEPNAME} PROPERTIES
    IMPORT_PREFIX ""
    PREFIX ""
    COMPILE_DEFINITIONS TARGET_COMPILE_FLAGS)

set_target_properties(${DEPNAME}_static PROPERTIES
    PREFIX "")

target_link_libraries(${DEPNAME} zlib)

# this is needed because the headers for zlib are only copied as part of
# the shared build
add_dependencies(${DEPNAME}_static zlib)

set(TARGET_COMPILE_FLAGS
    PNG_NO_MMX_CODE
    $<$<CONFIG:Debug>:PNG_DEBUG=1>
)

set_target_properties(${DEPNAME}_static PROPERTIES
    COMPILE_DEFINITIONS "${TARGET_COMPILE_FLAGS}")
