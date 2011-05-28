set(DEPNAME libmng)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../libmng_*.c")

set(HEADERS libmng.h libmng_conf.h libmng_types.h)

include_directories(../ ${CMAKE_BINARY_DIR}/dependencies/include)

cegui_add_library(${DEPNAME} SOURCES NONE)

set_target_properties(${DEPNAME} PROPERTIES DEFINE_SYMBOL MNG_BUILD_DLL)

target_link_libraries(${DEPNAME} zlib jpeg)

# this is needed because the headers for these deps are only copied as part of
# the shared build
add_dependencies(${DEPNAME}_static zlib jpeg)

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()


add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE"
                                                    "${CMAKE_BINARY_DIR}/dependencies/libmng-license.txt")

