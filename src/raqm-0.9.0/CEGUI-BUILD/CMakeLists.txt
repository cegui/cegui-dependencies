# Aside CEGUI-specific target generator this is merely a translation of meson.build shipped with raqm

set(DEPNAME raqm)

set(RAQM_VERSION_MAJOR 0) 
set(RAQM_VERSION_MINOR 9) 
set(RAQM_VERSION_MICRO 0) 
set(RAQM_VERSION "${RAQM_VERSION_MAJOR}.${RAQM_VERSION_MINOR}.${RAQM_VERSION_MICRO}")

set(HEADERS ../src/raqm.h)
set(SOURCES ../src/raqm.c)

configure_file(../src/raqm-version.h.in ${CMAKE_BINARY_DIR}/dependencies/include/raqm/raqm-version.h @ONLY)

# RAQM_SHEENBIDI is always disabled with CEGUI
# NB: meson is able to generate config without input, but for CMake we had to provide config.h.in
configure_file(config.h.in ${CMAKE_BINARY_DIR}/dependencies/include/raqm/config.h @ONLY)

foreach(_H_FILE ${HEADERS})
	# From CMake 3.20:
	#cmake_path(RELATIVE_PATH ${_H_FILE} "${CMAKE_CURRENT_SOURCE_DIR}/../src")
	get_filename_component(_H_FILE "${_H_FILE}" ABSOLUTE)
	file(RELATIVE_PATH _H_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../src" ${_H_FILE})
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../src/${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/raqm/${_H_FILE}" COPYONLY)
endforeach()                                

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../COPYING" "${CMAKE_BINARY_DIR}/dependencies/raqm-license.txt" COPYONLY)

cegui_add_library(${DEPNAME} SOURCES HEADERS)

if (MSVC AND TARGET ${DEPNAME})
	target_compile_definitions(${DEPNAME} PUBLIC "RAQM_API=__declspec(dllexport)")
endif()

if (TARGET ${DEPNAME}_static)
	add_dependencies(${DEPNAME}_static freetype harfbuzz fribidi)
endif()

get_property(ALL_TARGETS DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY BUILDSYSTEM_TARGETS)
foreach(TARGET_NAME IN LISTS ALL_TARGETS)

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

endforeach()
