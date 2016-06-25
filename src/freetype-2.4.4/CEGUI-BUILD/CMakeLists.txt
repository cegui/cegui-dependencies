set(DEPNAME freetype)

set(SOURCES
../src/base/ftsystem.c
../src/base/ftinit.c
../src/base/ftdebug.c
../src/base/ftbase.c
../src/base/ftbbox.c
../src/base/ftglyph.c
../src/base/ftbdf.c
../src/base/ftbitmap.c
../src/base/ftcid.c
../src/base/ftfstype.c
../src/base/ftgasp.c
../src/base/ftgxval.c
../src/base/ftlcdfil.c
../src/base/ftmm.c
../src/base/ftotval.c
../src/base/ftpatent.c
../src/base/ftpfr.c
../src/base/ftstroke.c
../src/base/ftsynth.c
../src/base/fttype1.c
../src/base/ftwinfnt.c
../src/base/ftxf86.c
../src/bdf/bdf.c
../src/cff/cff.c
../src/cid/type1cid.c
../src/pcf/pcf.c
../src/pfr/pfr.c
../src/sfnt/sfnt.c
../src/truetype/truetype.c
../src/type1/type1.c
../src/type42/type42.c
../src/winfonts/winfnt.c
../src/raster/raster.c
../src/smooth/smooth.c
../src/autofit/autofit.c
../src/cache/ftcache.c
../src/gzip/ftgzip.c
../src/lzw/ftlzw.c
../src/gxvalid/gxvalid.c
../src/otvalid/otvalid.c
../src/psaux/psaux.c
../src/pshinter/pshinter.c
../src/psnames/psnames.c)

if (APPLE)
#    list(APPEND SOURCES ../src/base/ftmac.c)
endif()

set(HEADERS )

include_directories(../include)

cegui_add_library(${DEPNAME} SOURCES HEADERS)

set(TARGET_COMPILE_FLAGS
    FT2_BUILD_LIBRARY
    $<$<CONFIG:Debug>:FT_DEBUG_LEVEL_ERROR;FT_DEBUG_LEVEL_TRACE>
)

set_target_properties(${DEPNAME} PROPERTIES
    COMPILE_DEFINITIONS "${TARGET_COMPILE_FLAGS}")

if (APPLE)
    set_target_properties(${DEPNAME} PROPERTIES
        LINK_FLAGS "-framework Carbon")
endif()

set_target_properties(${DEPNAME}_static PROPERTIES
    COMPILE_DEFINITIONS "${TARGET_COMPILE_FLAGS}")

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
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../docs/GPL.TXT"
                                                    "${CMAKE_BINARY_DIR}/dependencies/GPL.TXT")

