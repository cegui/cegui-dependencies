# See also an original ../CMakeLists.txt

if (NOT CMAKE_VERSION VERSION_LESS 3.3)
  # Allow symbol visibility settings also on static libraries. CMake < 3.3
  # only sets the property on a shared library build.
  cmake_policy(SET CMP0063 NEW)

  # Support new IN_LIST if() operator.
  cmake_policy(SET CMP0057 NEW)
endif ()

include(CheckIncludeFile)

set(DEPNAME freetype)

# TODO: this may be not required and may add to binary size with a redundant library copy in DLL, see CEGUI_HARFBUZZ_WITH_FREETYPE
set(CEGUI_FREETYPE_WITH_HARFBUZZ ON)
if (NOT CEGUI_BUILD_HARFBUZZ)
	set(CEGUI_FREETYPE_WITH_HARFBUZZ OFF)
endif()

set(VERSION_MAJOR "2")
set(VERSION_MINOR "11")
set(VERSION_PATCH "1")

# Generate LIBRARY_VERSION and LIBRARY_SOVERSION.
set(LIBTOOL_REGEX "version_info='([0-9]+):([0-9]+):([0-9]+)'")
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/../builds/unix/configure.raw"
  VERSION_INFO
  REGEX ${LIBTOOL_REGEX})
string(REGEX REPLACE
  ${LIBTOOL_REGEX} "\\1"
  LIBTOOL_CURRENT "${VERSION_INFO}")
string(REGEX REPLACE
  ${LIBTOOL_REGEX} "\\2"
  LIBTOOL_REVISION "${VERSION_INFO}")
string(REGEX REPLACE
  ${LIBTOOL_REGEX} "\\3"
  LIBTOOL_AGE "${VERSION_INFO}")

# This is what libtool does internally on Unix platforms.
math(EXPR LIBRARY_SOVERSION "${LIBTOOL_CURRENT} - ${LIBTOOL_AGE}")
set(LIBRARY_VERSION "${LIBRARY_SOVERSION}.${LIBTOOL_AGE}.${LIBTOOL_REVISION}")

# Add local cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../builds/cmake)

# Create the configuration file
if (UNIX)
  check_include_file("unistd.h" HAVE_UNISTD_H)
  check_include_file("fcntl.h" HAVE_FCNTL_H)

  file(READ "${CMAKE_CURRENT_SOURCE_DIR}/../builds/unix/ftconfig.h.in"
    FTCONFIG_H)
  if (HAVE_UNISTD_H)
    string(REGEX REPLACE
      "#undef +(HAVE_UNISTD_H)" "#define \\1 1"
      FTCONFIG_H "${FTCONFIG_H}")
  endif ()
  if (HAVE_FCNTL_H)
    string(REGEX REPLACE
      "#undef +(HAVE_FCNTL_H)" "#define \\1 1"
      FTCONFIG_H "${FTCONFIG_H}")
  endif ()
else ()
  file(READ "${CMAKE_CURRENT_SOURCE_DIR}/../include/freetype/config/ftconfig.h"
    FTCONFIG_H)
endif ()

set(FTCONFIG_H_NAME "${CMAKE_BINARY_DIR}/dependencies/include/freetype/config/ftconfig.h")
if (EXISTS "${FTCONFIG_H_NAME}")
  file(READ "${FTCONFIG_H_NAME}" ORIGINAL_FTCONFIG_H)
else ()
  set(ORIGINAL_FTCONFIG_H "")
endif ()
if (NOT (ORIGINAL_FTCONFIG_H STREQUAL FTCONFIG_H))
  file(WRITE "${FTCONFIG_H_NAME}" "${FTCONFIG_H}")
endif ()


# Create the options file
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/../include/freetype/config/ftoption.h"
  FTOPTION_H)
if (CEGUI_BUILD_ZLIB)
  string(REGEX REPLACE
    "/\\* +(#define +FT_CONFIG_OPTION_SYSTEM_ZLIB) +\\*/" "\\1"
    FTOPTION_H "${FTOPTION_H}")
endif ()
if (CEGUI_BUILD_LIBPNG)
  string(REGEX REPLACE
    "/\\* +(#define +FT_CONFIG_OPTION_USE_PNG) +\\*/" "\\1"
    FTOPTION_H "${FTOPTION_H}")
endif ()
if (CEGUI_FREETYPE_WITH_HARFBUZZ)
  string(REGEX REPLACE
    "/\\* +(#define +FT_CONFIG_OPTION_USE_HARFBUZZ) +\\*/" "\\1"
    FTOPTION_H "${FTOPTION_H}")
endif ()

set(FTOPTION_H_NAME "${CMAKE_BINARY_DIR}/dependencies/include/freetype/config/ftoption.h")
if (EXISTS "${FTOPTION_H_NAME}")
  file(READ "${FTOPTION_H_NAME}" ORIGINAL_FTOPTION_H)
else ()
  set(ORIGINAL_FTOPTION_H "")
endif ()
if (NOT (ORIGINAL_FTOPTION_H STREQUAL FTOPTION_H))
  file(WRITE "${FTOPTION_H_NAME}" "${FTOPTION_H}")
endif ()


file(GLOB PUBLIC_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/../include/ft2build.h" "${CMAKE_CURRENT_SOURCE_DIR}/../include/freetype/*.h")
file(GLOB PUBLIC_CONFIG_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/../include/freetype/config/*.h")
file(GLOB PRIVATE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/../include/freetype/internal/*.h")

set(BASE_SRCS
  src/autofit/autofit.c
  src/base/ftbase.c
  src/base/ftbbox.c
  src/base/ftbdf.c
  src/base/ftbitmap.c
  src/base/ftcid.c
  src/base/ftfstype.c
  src/base/ftgasp.c
  src/base/ftglyph.c
  src/base/ftgxval.c
  src/base/ftinit.c
  src/base/ftmm.c
  src/base/ftotval.c
  src/base/ftpatent.c
  src/base/ftpfr.c
  src/base/ftstroke.c
  src/base/ftsynth.c
  src/base/fttype1.c
  src/base/ftwinfnt.c
  src/bdf/bdf.c
  src/bzip2/ftbzip2.c
  src/cache/ftcache.c
  src/cff/cff.c
  src/cid/type1cid.c
  src/gzip/ftgzip.c
  src/lzw/ftlzw.c
  src/pcf/pcf.c
  src/pfr/pfr.c
  src/psaux/psaux.c
  src/pshinter/pshinter.c
  src/psnames/psnames.c
  src/raster/raster.c
  src/sdf/sdf.c
  src/sfnt/sfnt.c
  src/smooth/smooth.c
  src/truetype/truetype.c
  src/type1/type1.c
  src/type42/type42.c
  src/winfonts/winfnt.c
)

if (UNIX)
  list(APPEND BASE_SRCS "builds/unix/ftsystem.c")
elseif (WIN32)
  list(APPEND BASE_SRCS "builds/windows/ftsystem.c")
else ()
  list(APPEND BASE_SRCS "src/base/ftsystem.c")
endif ()

if (WIN32)
  enable_language(RC)
  list(APPEND BASE_SRCS builds/windows/ftdebug.c
                        src/base/ftver.rc)
elseif (WINCE)
  list(APPEND BASE_SRCS builds/wince/ftdebug.c)
else ()
  list(APPEND BASE_SRCS src/base/ftdebug.c)
endif ()

# Prevent erasing final configs with default ones
list(REMOVE_ITEM PUBLIC_CONFIG_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/../include/freetype/config/ftconfig.h")
list(REMOVE_ITEM PUBLIC_CONFIG_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/../include/freetype/config/ftoption.h")

set(HEADERS
  ${PUBLIC_HEADERS}
  ${PUBLIC_CONFIG_HEADERS}
  ${PRIVATE_HEADERS}
)

add_prefix_to_list(BASE_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/../")

foreach(_H_FILE ${HEADERS})
	# From CMake 3.20:
	#cmake_path(RELATIVE_PATH ${_H_FILE} "${CMAKE_CURRENT_SOURCE_DIR}/../src")
	get_filename_component(_H_FILE "${_H_FILE}" ABSOLUTE)
	file(RELATIVE_PATH _H_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../include" ${_H_FILE})
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../include/${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}" COPYONLY)
endforeach()

# Add headers that were already copied to the destination after we copy others
list(APPEND HEADERS ${FTCONFIG_H_NAME})
list(APPEND HEADERS ${FTOPTION_H_NAME})

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE.TXT" "${CMAKE_BINARY_DIR}/dependencies/freetype-license.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../docs/FTL.TXT" "${CMAKE_BINARY_DIR}/dependencies/FTL.TXT" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../docs/GPLv2.TXT" "${CMAKE_BINARY_DIR}/dependencies//GPLv2.TXT" COPYONLY)

cegui_add_library(${DEPNAME} BASE_SRCS HEADERS)

# Need this? Was in CEGUI Cmake for freetype 2.7.1
if (APPLE)
    set_target_properties(${DEPNAME} PROPERTIES
        LINK_FLAGS "-framework Carbon")
endif()

if (TARGET ${DEPNAME})
	if (WIN32)
		target_compile_definitions(
		  ${DEPNAME} PRIVATE DLL_EXPORT)
	endif()
	set_target_properties(freetype PROPERTIES
		VERSION ${LIBRARY_VERSION}
		SOVERSION ${LIBRARY_SOVERSION})
endif ()

get_property(ALL_TARGETS DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY BUILDSYSTEM_TARGETS)
foreach(TARGET_NAME IN LISTS ALL_TARGETS)

	set_target_properties(
	  ${TARGET_NAME} PROPERTIES
		C_VISIBILITY_PRESET hidden)

	target_compile_definitions(
	  ${TARGET_NAME} PRIVATE
		FT2_BUILD_LIBRARY
		#$<$<CONFIG:Debug>:FT_DEBUG_LEVEL_ERROR;FT_DEBUG_LEVEL_TRACE>
		)

	if (WIN32)
	  target_compile_definitions(
		${TARGET_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS)
	endif ()

	target_include_directories(${TARGET_NAME}
		PUBLIC
			${CMAKE_BINARY_DIR}/dependencies/include
		PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}/../include

			# Make <ftconfig.h> available for builds/unix/ftsystem.c.
			${CMAKE_BINARY_DIR}/dependencies/include/freetype/config
	)

	if (CEGUI_BUILD_ZLIB)
		target_link_libraries(${TARGET_NAME} PRIVATE zlib)
	endif ()
	if (CEGUI_BUILD_LIBPNG)
		target_link_libraries(${TARGET_NAME} PRIVATE libpng)
	endif ()
	if (CEGUI_FREETYPE_WITH_HARFBUZZ)
		target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_BINARY_DIR}/dependencies/include/harfbuzz)
		# Prevent circular dependency freetype <-> harfbuzz for dynamic libs.
		# Note that harfbuzz already depends on us so we can't make freetype_static -> harfbuzz dependency.
		target_link_libraries(${TARGET_NAME} PRIVATE harfbuzz_static)
	endif ()

endforeach()
