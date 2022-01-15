# Aside CEGUI-specific target generator this is merely a translation of meson.build shipped with fribidi

include(CheckSymbolExists) # CMake module
include(CheckIncludeFile) # CMake module
include(CheckCCompilerFlag) # CMake module
include(CheckTypeSize) # CMake module

set(DEPNAME fribidi)

set(FRIBIDI_MAJOR_VERSION 1) 
set(FRIBIDI_MINOR_VERSION 0) 
set(FRIBIDI_MICRO_VERSION 11) 
set(FRIBIDI_VERSION "${FRIBIDI_MAJOR_VERSION}.${FRIBIDI_MINOR_VERSION}.${FRIBIDI_MICRO_VERSION}")
set(FRIBIDI_INTERFACE_VERSION 4)
set(FRIBIDI_INTERFACE_AGE 0)
set(FRIBIDI_SOVERSION 0)
set(FRIBIDI_LIBVERSION "${FRIBIDI_SOVERSION}.${FRIBIDI_INTERFACE_VERSION}.0") # FRIBIDI_INTERFACE_AGE ?

check_c_compiler_flag("-fvisibility=hidden" HAS_VISIBILITY_HIDDEN_FLAG)

check_symbol_exists(memmove "string.h" HAVE_MEMMOVE)
check_symbol_exists(memset "string.h" HAVE_MEMSET)
check_symbol_exists(strdup "string.h" HAVE_STRDUP)
check_include_file("stdlib.h" HAVE_STDLIB_H)
check_include_file("string.h" HAVE_STRING_H)
check_include_file("memory.h" HAVE_MEMORY_H)
check_include_file("strings.h" HAVE_STRINGS_H)
check_include_file("sys/times.h" HAVE_SYS_TIMES_H)

# This is available pretty much everywhere
set(HAVE_STRINGIZE 1)

set(FRIBIDI_NO_DEPRECATED 1)

# NB: meson is able to generate config without input, but for CMake we had to provide config.h.in
configure_file(config.h.in ${CMAKE_BINARY_DIR}/dependencies/include/fribidi/config.h)

set(PACKAGE "fribidi")
set(PACKAGE_NAME "GNU FriBidi")
set(PACKAGE_BUGREPORT "https://github.com/fribidi/fribidi/issues/new")

check_type_size("int" SIZEOF_INT LANGUAGE C)

if (MSVC)
  set(FRIBIDI_MSVC_BUILD_PLACEHOLDER "#define FRIBIDI_BUILT_WITH_MSVC")
else()
  set(FRIBIDI_MSVC_BUILD_PLACEHOLDER "#undef FRIBIDI_BUILT_WITH_MSVC")
endif()

configure_file(../lib/fribidi-config.h.in ${CMAKE_BINARY_DIR}/dependencies/include/fribidi/fribidi-config.h @ONLY)

set(SOURCES
	fribidi.c
	fribidi-arabic.c
	fribidi-bidi.c
	fribidi-bidi-types.c
	fribidi-char-sets.c
	fribidi-char-sets-cap-rtl.c
	fribidi-char-sets-cp1255.c
	fribidi-char-sets-cp1256.c
	fribidi-char-sets-iso8859-6.c
	fribidi-char-sets-iso8859-8.c
	fribidi-char-sets-utf8.c
	fribidi-deprecated.c
	fribidi-joining.c
	fribidi-joining-types.c
	fribidi-mirroring.c
	fribidi-brackets.c
	fribidi-run.c
	fribidi-shape.c
)
  
set(HEADERS
	fribidi-arabic.h
	fribidi-begindecls.h
	fribidi-bidi.h
	fribidi-bidi-types.h
	fribidi-bidi-types-list.h
	fribidi-char-sets.h
	fribidi-char-sets-list.h
	fribidi-common.h
	fribidi-deprecated.h
	fribidi-enddecls.h
	fribidi-flags.h
	fribidi-joining.h
	fribidi-joining-types.h
	fribidi-joining-types-list.h
	fribidi-mirroring.h
	fribidi-brackets.h
	fribidi-shape.h
	fribidi-types.h
	fribidi-unicode.h
	fribidi.h

	# NB: these are not included in a meson.build list!
	fribidi-unicode-version.h
	bidi-type.tab.i
	joining-type.tab.i
	arabic-shaping.tab.i
	mirroring.tab.i
	brackets.tab.i
	brackets-type.tab.i
	arabic-misc.tab.i
)

add_prefix_to_list(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../lib/")
add_prefix_to_list(HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/../lib/")

cegui_add_library(${DEPNAME} SOURCES HEADERS)

get_property(ALL_TARGETS DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY BUILDSYSTEM_TARGETS)
foreach(TARGET_NAME IN LISTS ALL_TARGETS)

	target_include_directories(${TARGET_NAME}
		PUBLIC
			${CMAKE_BINARY_DIR}/dependencies/include
			${CMAKE_BINARY_DIR}/dependencies/include/fribidi
		PRIVATE
			#${CMAKE_CURRENT_SOURCE_DIR}
			../lib
			#../gen.tab			
	)
	target_compile_definitions(${TARGET_NAME} PUBLIC "HAVE_CONFIG_H" "FRIBIDI_BUILD")	
	set_target_properties(${TARGET_NAME} PROPERTIES
		VERSION ${FRIBIDI_LIBVERSION}
		SOVERSION ${FRIBIDI_SOVERSION})

	# Symbol visibility. Must explicitly make symbols public if default visibility is hidden.
	if (HAS_VISIBILITY_HIDDEN_FLAG)
		target_compile_options(${TARGET_NAME} PRIVATE "-fvisibility=hidden")
		target_compile_definitions(${TARGET_NAME} PRIVATE "FRIBIDI_ENTRY=__attribute__ ((visibility (\"default\")))")	
	else()
		if (WIN32 AND ${TARGET_NAME} STREQUAL "${DEPNAME}_static")
			target_compile_definitions(${TARGET_NAME} PRIVATE "FRIBIDI_LIB_STATIC")	
		endif()
	endif()

	if (CMAKE_BUILD_TYPE MATCHES DEBUG)
		target_compile_definitions(${TARGET_NAME} PRIVATE "DEBUG")	
	endif()

	# CEGUI-specific --------------------------------------------------------------
		
	foreach(_H_FILE ${HEADERS})
		# From CMake 3.20:
		#cmake_path(RELATIVE_PATH ${_H_FILE} "${CMAKE_CURRENT_SOURCE_DIR}/../lib")
		get_filename_component(_H_FILE "${_H_FILE}" ABSOLUTE)
		file(RELATIVE_PATH _H_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../lib" ${_H_FILE})
		add_custom_command(TARGET ${DEPNAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
			"${CMAKE_CURRENT_SOURCE_DIR}/../lib/${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/fribidi/${_H_FILE}")
	endforeach()                                

	add_custom_command(TARGET ${DEPNAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
		"${CMAKE_CURRENT_SOURCE_DIR}/../COPYING" "${CMAKE_BINARY_DIR}/dependencies/fribidi-license.txt")

endforeach()
