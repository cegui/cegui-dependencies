set(DEPNAME glew)

set(SOURCES ../src/glew.c)
set(HEADERS ../include/GL/glew.h ../include/GL/glxew.h ../include/GL/wglew.h)

foreach(_H_FILE ${HEADERS})
	# From CMake 3.20:
	#cmake_path(RELATIVE_PATH ${_H_FILE} "${CMAKE_CURRENT_SOURCE_DIR}/../include")
	get_filename_component(_H_FILE "${_H_FILE}" ABSOLUTE)
	file(RELATIVE_PATH _H_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../include" ${_H_FILE})
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../include/${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}" COPYONLY)
endforeach()                                

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE.txt" "${CMAKE_BINARY_DIR}/dependencies/glew-license.txt" COPYONLY)

cegui_add_library(${DEPNAME} SOURCES HEADERS)

if (WIN32)
    set_target_properties(${DEPNAME} PROPERTIES DEFINE_SYMBOL GLEW_BUILD)
    target_link_libraries(${DEPNAME} opengl32)
endif()

if (APPLE)
    set_target_properties(${DEPNAME} PROPERTIES LINK_FLAGS "-framework OpenGL")
endif()

set_target_properties(${DEPNAME}_static PROPERTIES COMPILE_DEFINITIONS GLEW_STATIC)

get_property(ALL_TARGETS DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY BUILDSYSTEM_TARGETS)
foreach(TARGET_NAME IN LISTS ALL_TARGETS)

	target_include_directories(${TARGET_NAME}
		PUBLIC
			${CMAKE_BINARY_DIR}/dependencies/include
		PRIVATE
			../include
	)

endforeach()
