set(DEPNAME tinyxml2)

set(TINYXML2_VERSION_MAJOR 9) 
set(TINYXML2_VERSION_MINOR 0) 
set(TINYXML2_VERSION_MICRO 0) 
set(TINYXML2_VERSION "${TINYXML2_VERSION_MAJOR}.${TINYXML2_VERSION_MINOR}.${TINYXML2_VERSION_MICRO}")

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

set(HEADERS ../tinyxml2.h)
set(SOURCES ../tinyxml2.cpp)

foreach(_H_FILE ${HEADERS})
	# From CMake 3.20:
	#cmake_path(RELATIVE_PATH ${_H_FILE} "${CMAKE_CURRENT_SOURCE_DIR}/..")
	get_filename_component(_H_FILE "${_H_FILE}" ABSOLUTE)
	file(RELATIVE_PATH _H_FILE "${CMAKE_CURRENT_SOURCE_DIR}/.." ${_H_FILE})
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/tinyxml2/${_H_FILE}" COPYONLY)
endforeach()                                

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE.txt" "${CMAKE_BINARY_DIR}/dependencies/tinyxml-license.txt" COPYONLY)

cegui_add_library(${DEPNAME} SOURCES HEADERS)

if (TARGET ${DEPNAME})
	target_compile_definitions(${DEPNAME} PUBLIC "TINYXML2_EXPORT")
	target_compile_definitions(${DEPNAME} INTERFACE "TINYXML2_IMPORT")
endif()

get_property(ALL_TARGETS DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY BUILDSYSTEM_TARGETS)
foreach(TARGET_NAME IN LISTS ALL_TARGETS)

	target_include_directories(${TARGET_NAME}
		PUBLIC
			${CMAKE_BINARY_DIR}/dependencies/include
		PRIVATE
			../
	)
	target_compile_definitions(
		${TARGET_NAME}
		PUBLIC $<$<CONFIG:Debug>:TINYXML2_DEBUG>
		PRIVATE $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
	)
	set_target_properties(${TARGET_NAME} PROPERTIES
		VERSION "${TINYXML2_VERSION}"
		SOVERSION "${TINYXML2_VERSION_MAJOR}"
		CXX_STANDARD 11)

endforeach()
