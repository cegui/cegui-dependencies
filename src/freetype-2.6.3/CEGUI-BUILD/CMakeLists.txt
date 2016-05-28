set(DEPNAME freetype)

set(SOURCES
  ../src/autofit/autofit.c
  ../src/base/ftbase.c
  ../src/base/ftbbox.c
  ../src/base/ftbdf.c
  ../src/base/ftbitmap.c
  ../src/base/ftcid.c
  ../src/base/ftfntfmt.c
  ../src/base/ftfstype.c
  ../src/base/ftgasp.c
  ../src/base/ftglyph.c
  ../src/base/ftgxval.c
  ../src/base/ftinit.c
  ../src/base/ftlcdfil.c
  ../src/base/ftmm.c
  ../src/base/ftotval.c
  ../src/base/ftpatent.c
  ../src/base/ftpfr.c
  ../src/base/ftstroke.c
  ../src/base/ftsynth.c
  ../src/base/ftsystem.c
  ../src/base/fttype1.c
  ../src/base/ftwinfnt.c
  ../src/bdf/bdf.c
  ../src/bzip2/ftbzip2.c
  ../src/cache/ftcache.c
  ../src/cff/cff.c
  ../src/cid/type1cid.c
  ../src/gzip/ftgzip.c
  ../src/lzw/ftlzw.c
  ../src/pcf/pcf.c
  ../src/pfr/pfr.c
  ../src/psaux/psaux.c
  ../src/pshinter/pshinter.c
  ../src/psnames/psnames.c
  ../src/raster/raster.c
  ../src/sfnt/sfnt.c
  ../src/smooth/smooth.c
  ../src/truetype/truetype.c
  ../src/type1/type1.c
  ../src/type42/type42.c
  ../src/winfonts/winfnt.c)
  
if (WIN32)
  set(SOURCES ${SOURCES} ../builds/windows/ftdebug.c)
elseif (WINCE)
  set(SOURCES ${SOURCES} ../builds/wince/ftdebug.c)
else ()
  set(SOURCES ${SOURCES} ../src/base/ftdebug.c)
endif ()

set(HEADERS )

include_directories(../include)

cegui_add_library(${DEPNAME} SOURCES HEADERS)

set_target_properties(${DEPNAME} PROPERTIES
    COMPILE_DEFINITIONS FT2_BUILD_LIBRARY
	COMPILE_DEFINITIONS_DEBUG "FT_DEBUG_LEVEL_ERROR;FT_DEBUG_LEVEL_TRACE")

if (APPLE)
    set_target_properties(${DEPNAME} PROPERTIES
        LINK_FLAGS "-framework Carbon")
endif()

set_target_properties(${DEPNAME}_static PROPERTIES
    COMPILE_DEFINITIONS FT2_BUILD_LIBRARY
	COMPILE_DEFINITIONS_DEBUG "FT_DEBUG_LEVEL_ERROR;FT_DEBUG_LEVEL_TRACE")

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/../include/"
                                                   "${CMAKE_BINARY_DIR}/dependencies/include")

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../docs/LICENSE.TXT"
                                                    "${CMAKE_BINARY_DIR}/dependencies/freetype-license.txt")
add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../docs/FTL.TXT"
                                                    "${CMAKE_BINARY_DIR}/dependencies/FTL.TXT")
add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../docs/GPLv2.TXT"
                                                    "${CMAKE_BINARY_DIR}/dependencies/GPLv2.TXT")

