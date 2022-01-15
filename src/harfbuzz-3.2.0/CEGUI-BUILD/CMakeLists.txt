# Aside CEGUI-specific target generator this is merely a translation of CMakeLists.txt / meson.build shipped with harfbuzz

include (CheckSymbolExists) # CMake module
include (CheckIncludeFile) # CMake module

# Functions -------------------------------------------------------------------

function (extract_make_variable variable makefile_source)
  string(REGEX MATCH "${variable} = ([^$]+)\\$" temp "${makefile_source}")
  string(REGEX MATCHALL "[^ \n\t\\]+" listVar "${CMAKE_MATCH_1}")
  set (${variable} ${listVar} PARENT_SCOPE)
endfunction ()

function (add_prefix_to_list var prefix)
  set (listVar "")
  foreach (f ${${var}})
    list(APPEND listVar "${prefix}${f}")
  endforeach ()
  set (${var} "${listVar}" PARENT_SCOPE)
endfunction ()

#------------------------------------------------------------------------------

set(DEPNAME harfbuzz)

set(HB_VERSION_MAJOR 3) 
set(HB_VERSION_MINOR 2) 
set(HB_VERSION_MICRO 0) 
set(HB_VERSION "${HB_VERSION_MAJOR}.${HB_VERSION_MINOR}.${HB_VERSION_MICRO}")

check_include_file(unistd.h HAVE_UNISTD_H)
check_include_file(sys/mman.h HAVE_SYS_MMAN_H)
check_include_file(stdbool.h HAVE_STDBOOL_H)

#if (NOT MSVC)
#  set(THREADS_PREFER_PTHREAD_FLAG ON)
#  find_package(Threads)
#  if (CMAKE_USE_PTHREADS_INIT)
#    add_definitions("-DHAVE_PTHREAD")
#    list(APPEND THIRD_PARTY_LIBS Threads::Threads)
#  endif ()
#endif ()

if (MSVC)
  add_definitions(-wd4244 -wd4267 -D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_WARNINGS)
endif ()

file(READ ${CMAKE_CURRENT_SOURCE_DIR}/../src/Makefile.sources SRCSOURCES)
extract_make_variable(HB_BASE_headers ${SRCSOURCES})

# Can also use amalgam source when provided: ${CMAKE_CURRENT_SOURCE_DIR}/src/harfbuzz.cc)
extract_make_variable(HB_BASE_sources ${SRCSOURCES})
#extract_make_variable(HB_BASE_RAGEL_GENERATED_sources ${SRCSOURCES})

# Freetype
# TODO: find_package(Freetype REQUIRED) -> FREETYPE_INCLUDE_DIRS, FREETYPE_LIBRARIES ?
# FIXME: extract_make_variable is imperfect: extract_make_variable(HB_FT_sources ${SRCSOURCES})
# FIXME: extract_make_variable is imperfect: extract_make_variable(HB_FT_headers ${SRCSOURCES})
set(HB_FT_sources hb-ft.cc)
set(HB_FT_headers hb-ft.h)
check_symbol_exists(FT_Get_Var_Blend_Coordinates "freetype/freetype.h" HAVE_FT_GET_VAR_BLEND_COORDINATES)
check_symbol_exists(FT_Set_Var_Blend_Coordinates "freetype/freetype.h" HAVE_FT_SET_VAR_BLEND_COORDINATES)
check_symbol_exists(HAVE_FT_DONE_MM_VAR "freetype/freetype.h" HAVE_FT_DONE_MM_VAR)

# NB: meson is able to generate config without input, but for CMake we had to provide config.h.in
configure_file(config.h.in ${CMAKE_BINARY_DIR}/dependencies/include/harfbuzz/config.h @ONLY)

## Define sources and headers of the project
set(project_sources ${HB_BASE_sources} ${HB_FT_sources}) # ${HB_BASE_RAGEL_GENERATED_sources}) 
set(project_headers ${HB_BASE_headers} ${HB_FT_headers})

add_prefix_to_list(project_headers "${CMAKE_CURRENT_SOURCE_DIR}/../src/")
add_prefix_to_list(project_sources "${CMAKE_CURRENT_SOURCE_DIR}/../src/")
set(HEADERS ${project_headers})
set(SOURCES ${project_sources})

cegui_add_library(${DEPNAME} SOURCES HEADERS)

get_property(HB_ALL_TARGETS DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY BUILDSYSTEM_TARGETS)
foreach(TARGET_NAME IN LISTS HB_ALL_TARGETS)

	target_include_directories(${TARGET_NAME}
		PUBLIC
			${CMAKE_BINARY_DIR}/dependencies/include/harfbuzz
		PRIVATE
			../src
			${CMAKE_BINARY_DIR}/dependencies/include
	)
	target_link_libraries(${TARGET_NAME} freetype) # usp10 gdi32 rpcrt4) # See HB_HAVE_UNISCRIBE, HB_HAVE_GDI, HB_HAVE_DIRECTWRITE on WIN32
	target_compile_definitions(${TARGET_NAME} PUBLIC "HAVE_CONFIG_H" "HAVE_FREETYPE=1")	
	set_target_properties(${TARGET_NAME} PROPERTIES
		LINKER_LANGUAGE CXX #Files end with .c so cmake can't decide what the hell this is
		CXX_STANDARD 11
		CXX_STANDARD_REQUIRED ON)
	
	if (MSVC)
		# Disable RTTI
		target_compile_options(${TARGET_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:/GR->)
	endif()

	# CEGUI-specific --------------------------------------------------------------

	foreach(_H_FILE ${HEADERS})
		# From CMake 3.20:
		#cmake_path(RELATIVE_PATH ${_H_FILE} "${CMAKE_CURRENT_SOURCE_DIR}/../src")
		get_filename_component(_H_FILE "${_H_FILE}" ABSOLUTE)
		file(RELATIVE_PATH _H_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../src" ${_H_FILE})
		add_custom_command(TARGET ${DEPNAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
			"${CMAKE_CURRENT_SOURCE_DIR}/../src/${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/harfbuzz/${_H_FILE}")
	endforeach()                                

	add_custom_command(TARGET ${DEPNAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
		"${CMAKE_CURRENT_SOURCE_DIR}/../COPYING" "${CMAKE_BINARY_DIR}/dependencies/harfbuzz-license.txt")

endforeach()

if (TARGET ${DEPNAME}_static)
	add_dependencies(${DEPNAME}_static freetype)
endif()

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
  # Make symbols link locally
  include (CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG(-Bsymbolic-functions CXX_SUPPORTS_FLAG_BSYMB_FUNCS)
  if (CXX_SUPPORTS_FLAG_BSYMB_FUNCS)
    link_libraries(-Bsymbolic-functions)
  endif ()

  if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Make sure we don't link to libstdc++
    # No threadsafe statics as we do it ourselves
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions -fno-threadsafe-statics")
    set (CMAKE_CXX_IMPLICIT_LINK_LIBRARIES "m") # libm
    set (CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "")
    set_target_properties(${DEPNAME} PROPERTIES LINKER_LANGUAGE C)
    set_target_properties(${DEPNAME}_static PROPERTIES LINKER_LANGUAGE C)
  endif ()
endif ()
