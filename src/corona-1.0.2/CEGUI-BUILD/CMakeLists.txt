set(DEPNAME corona)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	"../src/*.cpp"
	"../src/libungif-4.1.0/*.c")

set(HEADERS corona.h)

include_directories(
	../src
	../src/libungif-4.1.0
    ${CMAKE_BINARY_DIR}/dependencies/include)

cegui_add_library(${DEPNAME} SOURCES NONE)

target_link_libraries(${DEPNAME} libpng jpeg)

# this is needed because the headers for these deps are only copied as part of
# the shared build
add_dependencies(${DEPNAME}_static libpng jpeg)

set_target_properties(${DEPNAME} PROPERTIES
    DEFINE_SYMBOL CORONA_EXPORTS)

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../src/${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../doc/license.txt"
                                                    "${CMAKE_BINARY_DIR}/dependencies/corona-license.txt")

