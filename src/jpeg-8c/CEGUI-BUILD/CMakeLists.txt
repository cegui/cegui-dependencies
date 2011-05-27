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

if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../jconfig.h")
    if (WIN32)
        execute_process(COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../jconfig.vc"
                                                        "${CMAKE_CURRENT_SOURCE_DIR}/../jconfig.h")
    else()
        execute_process(COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../jconfig.mac"
                                                        "${CMAKE_CURRENT_SOURCE_DIR}/../jconfig.h")
    endif()
endif()

cegui_add_library(${DEPNAME} SOURCES NONE)

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../README"
                                                    "${CMAKE_BINARY_DIR}/dependencies/jpeg-README.txt")


