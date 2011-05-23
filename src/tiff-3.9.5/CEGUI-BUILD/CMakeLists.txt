set(DEPNAME libtiff)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../libtiff/tif_*.c")
list(REMOVE_ITEM SOURCES
	"../libtiff/tif_acorn.c"
	"../libtiff/tif_apple.c"
	"../libtiff/tif_atari.c"
	"../libtiff/tif_msdos.c"
	"../libtiff/tif_win3.c"
	"../libtiff/tif_win32.c"
)

set(HEADERS
    tiff.h
    tiffconf.h
    tiffio.h
    tiffvers.h)

include_directories(../ "${CMAKE_BINARY_DIR}/include")

if (MSVC)
    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../libtiff/tiffconf.h")
        execute_process(COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../libtiff/tiffconf.vc.h"
                                                         "${CMAKE_CURRENT_SOURCE_DIR}/../libtiff/tiffconf.h")
    endif()
    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../libtiff/tif_config.h")
        execute_process(COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../libtiff/tif_config.vc.h"
                                                         "${CMAKE_CURRENT_SOURCE_DIR}/../libtiff/tif_config.h")
    endif()
endif()

cegui_add_library(${DEPNAME} SOURCES NONE)

target_link_libraries(${DEPNAME} zlib)

set_target_properties(${DEPNAME} PROPERTIES COMPILE_DEFINITIONS
    "USE_WIN_CRT_LIB=1;WINMODE_CONSOLE=1;CCITT_SUPPORT=1;PACKBITS_SUPPORT=1;LZW_SUPPORT=1;THUNDER_SUPPORT=1;NEXT_SUPPORT=1;LOGLUV_SUPPORT=1;ZIP_SUPPORT=1;STRIPCHOP_SUPPORT=1;STRIP_SIZE_DEFAULT=8192;EXTRASAMPLE_AS_ALPHA_SUPPORT=1;CHECK_JPEG_YCBCR_SUBSAMPLING=1")

set_target_properties(${DEPNAME}_static PROPERTIES COMPILE_DEFINITIONS
    "USE_WIN_CRT_LIB=1;WINMODE_CONSOLE=1;CCITT_SUPPORT=1;PACKBITS_SUPPORT=1;LZW_SUPPORT=1;THUNDER_SUPPORT=1;NEXT_SUPPORT=1;LOGLUV_SUPPORT=1;ZIP_SUPPORT=1;STRIPCHOP_SUPPORT=1;STRIP_SIZE_DEFAULT=8192;EXTRASAMPLE_AS_ALPHA_SUPPORT=1;CHECK_JPEG_YCBCR_SUBSAMPLING=1")

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../libtiff/${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/include/${_H_FILE}")
endforeach()

