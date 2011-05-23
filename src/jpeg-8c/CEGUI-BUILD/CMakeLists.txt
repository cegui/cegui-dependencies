set(DEPNAME jpeg)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../j*.c")
list(REMOVE_ITEM SOURCES
	"../jpegtran.c"
	"../jmemansi.c"
	"../jmemname.c"
	"../jmemdos.c"
	"../jmemmac.c")

set(HEADERS jerror.h jconfig.h jmorecfg.h jpeglib.h)

include_directories(../)

if (WIN32)
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../jconfig.vc"
                                                     "${CMAKE_CURRENT_SOURCE_DIR}/../jconfig.h")
endif()

cegui_add_library(${DEPNAME} SOURCES NONE)

set_target_properties(${DEPNAME}_static PROPERTIES
    COMPILE_DEFINITIONS PNG_NO_MMX_CODE)

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/include/${_H_FILE}")
endforeach()



