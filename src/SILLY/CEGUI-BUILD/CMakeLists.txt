set(DEPNAME SILLY)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../src/*.cpp")
file(GLOB SOURCES_LOADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../src/loaders/*.cpp")
list(APPEND SOURCES ${SOURCES_LOADERS})

include_directories(../include "${CMAKE_BINARY_DIR}/include")

cegui_add_library(${DEPNAME} SOURCES HEADERS)

target_link_libraries(${DEPNAME} libpng jpeg)

set_target_properties(${DEPNAME} PROPERTIES
    COMPILE_DEFINITIONS "SILLY_HAVE_JPG;SILLY_HAVE_PNG"
	COMPILE_DEFINITIONS_DEBUG "SILLY_OPT_DEBUG")

set_target_properties(${DEPNAME}_static PROPERTIES
    COMPILE_DEFINITIONS "SILLY_STATIC;SILLY_HAVE_JPG;SILLY_HAVE_PNG"
	COMPILE_DEFINITIONS_DEBUG "SILLY_OPT_DEBUG")

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/../include/"
                                                   "${CMAKE_BINARY_DIR}/include")


