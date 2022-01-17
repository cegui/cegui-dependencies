set(DEPNAME zlib)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../*.c")
list(REMOVE_ITEM SOURCES ../example.c ../minigzip.c)

set(HEADERS ../zlib.h ../zconf.h)

foreach(_H_FILE ${HEADERS})
	# From CMake 3.20:
	#cmake_path(RELATIVE_PATH ${_H_FILE} "${CMAKE_CURRENT_SOURCE_DIR}/../src")
	get_filename_component(_H_FILE "${_H_FILE}" ABSOLUTE)
	file(RELATIVE_PATH _H_FILE "${CMAKE_CURRENT_SOURCE_DIR}/.." ${_H_FILE})
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}" COPYONLY)
endforeach()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../README" "${CMAKE_BINARY_DIR}/dependencies/zlib-README.txt" COPYONLY)

cegui_add_library(${DEPNAME} SOURCES HEADERS)

set_target_properties(${DEPNAME} PROPERTIES
    DEFINE_SYMBOL ZLIB_DLL)

get_property(ALL_TARGETS DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY BUILDSYSTEM_TARGETS)
foreach(TARGET_NAME IN LISTS ALL_TARGETS)

	target_include_directories(${TARGET_NAME}
		PUBLIC
			${CMAKE_BINARY_DIR}/dependencies/include
		PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}/..
	)

	if (APPLE)
		target_compile_definitions(${TARGET_NAME} PUBLIC "Z_HAVE_UNISTD_H")	
	elseif (MSVC)
		target_compile_options(${TARGET_NAME} PRIVATE
			/wd4996 # Posix name deprecated
		)
	endif()

endforeach()
