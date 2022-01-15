# Aside CEGUI-specific target generator this is merely a translation of meson.build shipped with raqm

include(CheckSymbolExists) # CMake module

set(DEPNAME raqm)

set(RAQM_VERSION_MAJOR 0) 
set(RAQM_VERSION_MINOR 8) 
set(RAQM_VERSION_MICRO 0) 
set(RAQM_VERSION "${RAQM_VERSION_MAJOR}.${RAQM_VERSION_MINOR}.${RAQM_VERSION_MICRO}")

set(HEADERS ../src/raqm.h)
set(SOURCES ../src/raqm.c)

configure_file(../src/raqm-version.h.in ${CMAKE_BINARY_DIR}/dependencies/include/raqm/raqm-version.h @ONLY)

# FIXME: get rid of versions in folder names? It is too easy to forget to change it here!
#set(HARFBUZZ_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/../../harfbuzz-3.2.0/src/hb.h")
#set(FREETYPE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/../../freetype-2.7.1/include/freetype/freetype.h")
set(HARFBUZZ_HEADERS "hb.h")
set(FREETYPE_HEADERS "freetype/freetype.h")
check_symbol_exists(FT_Get_Transform ${FREETYPE_HEADERS} HAVE_FT_GET_TRANSFORM)
check_symbol_exists(hb_buffer_set_invisible_glyph ${HARFBUZZ_HEADERS} HAVE_HB_BUFFER_SET_INVISIBLE_GLYPH) # "hb-buffer.h"
check_symbol_exists(HB_BUFFER_FLAG_REMOVE_DEFAULT_IGNORABLES ${HARFBUZZ_HEADERS} HAVE_DECL_HB_BUFFER_FLAG_REMOVE_DEFAULT_IGNORABLES)
# NB: meson is able to generate config without input, but for CMake we had to provide config.h.in
configure_file(config.h.in ${CMAKE_BINARY_DIR}/dependencies/include/raqm/config.h @ONLY)

cegui_add_library(${DEPNAME} SOURCES HEADERS)

if (MSVC AND TARGET ${DEPNAME})
	target_compile_definitions(${DEPNAME} PUBLIC "RAQM_API=__declspec(dllexport)")
endif()

if (TARGET ${DEPNAME}_static)
	add_dependencies(${DEPNAME}_static freetype harfbuzz fribidi)
endif()

get_property(RAQM_ALL_TARGETS DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY BUILDSYSTEM_TARGETS)
foreach(TARGET_NAME IN LISTS RAQM_ALL_TARGETS)

	target_include_directories(${TARGET_NAME}
		PUBLIC
			${CMAKE_BINARY_DIR}/dependencies/include
			${CMAKE_BINARY_DIR}/dependencies/include/raqm
			${CMAKE_BINARY_DIR}/dependencies/include/fribidi
			${CMAKE_BINARY_DIR}/dependencies/include/harfbuzz
		PRIVATE
			../src
	)
	target_link_libraries(${TARGET_NAME} freetype harfbuzz fribidi)
	target_compile_definitions(${TARGET_NAME} PUBLIC "HAVE_CONFIG_H")	
	set_target_properties(${TARGET_NAME} PROPERTIES
		LINKER_LANGUAGE CXX #Files end with .c so cmake can't decide what the hell this is
		C_STANDARD 99
		CXX_STANDARD 11)

	# CEGUI-specific --------------------------------------------------------------
		
	foreach(_H_FILE ${HEADERS})
		# From CMake 3.20:
		#cmake_path(RELATIVE_PATH ${_H_FILE} "${CMAKE_CURRENT_SOURCE_DIR}/../src")
		get_filename_component(_H_FILE "${_H_FILE}" ABSOLUTE)
		file(RELATIVE_PATH _H_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../src" ${_H_FILE})
		add_custom_command(TARGET ${DEPNAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
			"${CMAKE_CURRENT_SOURCE_DIR}/../src/${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/raqm/${_H_FILE}")
	endforeach()                                

	add_custom_command(TARGET ${DEPNAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
		"${CMAKE_CURRENT_SOURCE_DIR}/../COPYING" "${CMAKE_BINARY_DIR}/dependencies/raqm-license.txt")

endforeach()
