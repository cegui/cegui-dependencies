set(DEPNAME jpeg)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../j*.c")
list(REMOVE_ITEM SOURCES
	"../jpegtran.c"
	"../jmemansi.c"
	"../jmemname.c"
	"../jmemdos.c"
	"../jmemmac.c")

set(HEADERS
	../jerror.h
	../jconfig.h
	../jmorecfg.h
	../jpeglib.h)

if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../jconfig.h")
    if (WIN32)
		configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../jconfig.vc" "${CMAKE_CURRENT_SOURCE_DIR}/../jconfig.h" COPYONLY)
    else()
		configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../jconfig.mac" "${CMAKE_CURRENT_SOURCE_DIR}/../jconfig.h" COPYONLY)
    endif()
endif()

foreach(_H_FILE ${HEADERS})
	# From CMake 3.20:
	#cmake_path(RELATIVE_PATH ${_H_FILE} "${CMAKE_CURRENT_SOURCE_DIR}/../src")
	get_filename_component(_H_FILE "${_H_FILE}" ABSOLUTE)
	file(RELATIVE_PATH _H_FILE "${CMAKE_CURRENT_SOURCE_DIR}/.." ${_H_FILE})
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}" COPYONLY)
endforeach()                                

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../README" "${CMAKE_BINARY_DIR}/dependencies/jpeg-README.txt" COPYONLY)

cegui_add_library(${DEPNAME} SOURCES HEADERS)

get_property(ALL_TARGETS DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY BUILDSYSTEM_TARGETS)
foreach(TARGET_NAME IN LISTS ALL_TARGETS)

	target_include_directories(${TARGET_NAME}
		PUBLIC
			${CMAKE_BINARY_DIR}/dependencies
		PRIVATE
			../
	)

endforeach()
