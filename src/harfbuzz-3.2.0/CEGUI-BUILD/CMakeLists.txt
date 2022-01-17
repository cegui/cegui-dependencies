# Aside CEGUI-specific target generator this is merely a translation of CMakeLists.txt / meson.build shipped with harfbuzz

include(CheckSymbolExists) # CMake module
include(CheckIncludeFile) # CMake module
include(CheckCCompilerFlag) # CMake module
#include(CheckLinkerFlag) # CMake module

set(DEPNAME harfbuzz)

# TODO: this may be not required and may add to binary size with a redundant library copy in DLL, see CEGUI_FREETYPE_WITH_HARFBUZZ
set(CEGUI_HARFBUZZ_WITH_FREETYPE ON)
if (NOT CEGUI_BUILD_FREETYPE2)
	set(CEGUI_HARFBUZZ_WITH_FREETYPE OFF)
endif()

set(HB_VERSION_MAJOR 3)
set(HB_VERSION_MINOR 2)
set(HB_VERSION_MICRO 0)
set(HB_VERSION "${HB_VERSION_MAJOR}.${HB_VERSION_MINOR}.${HB_VERSION_MICRO}")

check_c_compiler_flag("/utf-8" HAS_UTF8_FLAG)
#check_linker_flag("C" "-Bsymbolic-functions" HAS_B_SYMBOLIC_FUNCTIONS) # FIXME: it says that the language is not supported!

check_include_file(unistd.h HAVE_UNISTD_H)
check_include_file(sys/mman.h HAVE_SYS_MMAN_H)
check_include_file(stdbool.h HAVE_STDBOOL_H)
check_include_file(xlocale.h HAVE_XLOCALE_H)

check_symbol_exists(atexit "stdlib.h" HAVE_ATEXIT)
check_symbol_exists(mprotect "sys/mman.h" HAVE_MPROTECT)
check_symbol_exists(sysconf "unistd.h" HAVE_SYSCONF)
check_symbol_exists(getpagesize "unistd.h" HAVE_GETPAGESIZE)
check_symbol_exists(mmap "sys/mman.h" HAVE_MMAP)
check_symbol_exists(isatty "unistd.h" HAVE_ISATTY)
check_symbol_exists(uselocale "locale.h" HAVE_USELOCALE)
check_symbol_exists(newlocale "locale.h" HAVE_NEWLOCALE)

#if (NOT MSVC)
#  set(THREADS_PREFER_PTHREAD_FLAG ON)
#  find_package(Threads)
#  if (CMAKE_USE_PTHREADS_INIT)
#    add_definitions("-DHAVE_PTHREAD")
#    list(APPEND THIRD_PARTY_LIBS Threads::Threads)
#  endif ()
#endif ()

file(READ ${CMAKE_CURRENT_SOURCE_DIR}/../src/Makefile.sources SRCSOURCES)
extract_make_variable(HB_BASE_headers ${SRCSOURCES})

# Can also use amalgam source when provided: ${CMAKE_CURRENT_SOURCE_DIR}/src/harfbuzz.cc)
extract_make_variable(HB_BASE_sources ${SRCSOURCES})
#extract_make_variable(HB_BASE_RAGEL_GENERATED_sources ${SRCSOURCES})

# Freetype
if (CEGUI_HARFBUZZ_WITH_FREETYPE)
	set(HAVE_FREETYPE 1)
	# TODO: find_package(Freetype REQUIRED) -> FREETYPE_INCLUDE_DIRS, FREETYPE_LIBRARIES ?
	# FIXME: extract_make_variable is imperfect: extract_make_variable(HB_FT_sources ${SRCSOURCES})
	# FIXME: extract_make_variable is imperfect: extract_make_variable(HB_FT_headers ${SRCSOURCES})
	set(HB_FT_sources hb-ft.cc)
	set(HB_FT_headers hb-ft.h)
	set(CMAKE_REQUIRED_INCLUDES "${CMAKE_BINARY_DIR}/dependencies/include/")
	cegui_check_symbol_exists(FT_Get_Var_Blend_Coordinates "freetype/ftmm.h" HAVE_FT_GET_VAR_BLEND_COORDINATES)
	cegui_check_symbol_exists(FT_Set_Var_Blend_Coordinates "freetype/ftmm.h" HAVE_FT_SET_VAR_BLEND_COORDINATES)
	cegui_check_symbol_exists(FT_Done_MM_Var "freetype/ftmm.h" HAVE_FT_DONE_MM_VAR)
endif()

# NB: meson is able to generate config without input, but for CMake we had to provide config.h.in
configure_file(config.h.in ${CMAKE_BINARY_DIR}/dependencies/include/harfbuzz/config.h)

## Define sources and headers of the project
set(project_sources ${HB_BASE_sources} ${HB_FT_sources}) # ${HB_BASE_RAGEL_GENERATED_sources}) 
set(project_headers ${HB_BASE_headers} ${HB_FT_headers})

add_prefix_to_list(project_headers "${CMAKE_CURRENT_SOURCE_DIR}/../src/")
add_prefix_to_list(project_sources "${CMAKE_CURRENT_SOURCE_DIR}/../src/")
set(HEADERS ${project_headers})
set(SOURCES ${project_sources})

foreach(_H_FILE ${HEADERS})
	# From CMake 3.20:
	#cmake_path(RELATIVE_PATH ${_H_FILE} "${CMAKE_CURRENT_SOURCE_DIR}/../src")
	get_filename_component(_H_FILE "${_H_FILE}" ABSOLUTE)
	file(RELATIVE_PATH _H_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../src" ${_H_FILE})
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../src/${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/harfbuzz/${_H_FILE}" COPYONLY)
endforeach()                                

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../COPYING" "${CMAKE_BINARY_DIR}/dependencies/harfbuzz-license.txt" COPYONLY)

cegui_add_library(${DEPNAME} SOURCES HEADERS)

get_property(ALL_TARGETS DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY BUILDSYSTEM_TARGETS)
foreach(TARGET_NAME IN LISTS ALL_TARGETS)

	target_include_directories(${TARGET_NAME}
		PUBLIC
			${CMAKE_BINARY_DIR}/dependencies/include/harfbuzz
		PRIVATE
			../src
			${CMAKE_BINARY_DIR}/dependencies/include
	)
	#target_link_libraries(${TARGET_NAME} usp10 gdi32 rpcrt4) # See HB_HAVE_UNISCRIBE, HB_HAVE_GDI, HB_HAVE_DIRECTWRITE on WIN32
	target_compile_definitions(${TARGET_NAME} PUBLIC "HAVE_CONFIG_H")	
	set_target_properties(${TARGET_NAME} PROPERTIES
		LINKER_LANGUAGE CXX #Files end with .c so cmake can't decide what the hell this is
		CXX_STANDARD 11
		CXX_STANDARD_REQUIRED ON)
	
	if (MSVC)
		target_compile_definitions(${TARGET_NAME} PUBLIC "_CRT_SECURE_NO_WARNINGS" "_CRT_NONSTDC_NO_WARNINGS")	
		target_compile_options(${TARGET_NAME} PRIVATE
			$<$<COMPILE_LANGUAGE:CXX>:/GR->  # disable RTTI
			$<$<COMPILE_LANGUAGE:CXX>:/EHs-> # disable exception handling
			$<$<COMPILE_LANGUAGE:CXX>:/EHc-> # disable exception handling
			$<${HAS_UTF8_FLAG}:/utf-8>
			#/wd4018
			#/wd4146
			/wd4244 # Conversion - possible loss of data
			#/wd4305
			#/wd4267
		)
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		# Make sure we don't link to libstdc++
		target_compile_options(${TARGET_NAME} PRIVATE
			"-fno-rtti"                    # disable RTTI
			"-fno-exceptions"              # disable exception handling
			"-fno-threadsafe-statics"      # no threadsafe statics as we do it ourselves
			"-fvisibility-inlines-hidden"
		)
		set_target_properties(${DEPNAME} PROPERTIES LINKER_LANGUAGE C)
	endif()

	if (HAS_B_SYMBOLIC_FUNCTIONS)
		target_link_options(${TARGET_NAME} PRIVATE "-Bsymbolic-functions")
	endif()

	if (CEGUI_HARFBUZZ_WITH_FREETYPE)
		target_compile_definitions(${TARGET_NAME} PUBLIC "HAVE_FREETYPE=1")	
		target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_BINARY_DIR}/dependencies/include)
		# Prevent circular dependency freetype <-> harfbuzz for dynamic libs
		if(${TARGET_NAME} STREQUAL ${DEPNAME})
			target_link_libraries(${TARGET_NAME} PRIVATE freetype)
		else()
			add_dependencies(${TARGET_NAME} freetype_static)
			target_link_libraries(${TARGET_NAME} PRIVATE freetype_static)
		endif()
	endif ()

endforeach()

if (WIN32 AND NOT MINGW AND TARGET ${DEPNAME})
	target_compile_definitions(${DEPNAME} PUBLIC "HB_DLL_EXPORT")
endif()

if (MSVC)
	# Disable exceptions
	if(CMAKE_CXX_FLAGS MATCHES "/EHsc")
		string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	endif()
endif()

if (UNIX OR MINGW)
  if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set (CMAKE_CXX_IMPLICIT_LINK_LIBRARIES "m") # libm
    set (CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "")
  endif ()
endif ()
