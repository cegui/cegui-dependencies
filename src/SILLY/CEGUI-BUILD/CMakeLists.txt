set(DEPNAME SILLY)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../src/*.cpp")
file(GLOB SOURCES_LOADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../src/loaders/*.cpp")
list(APPEND SOURCES ${SOURCES_LOADERS})

include_directories(../include "${CMAKE_BINARY_DIR}/dependencies/include")

cegui_add_library(${DEPNAME} SOURCES HEADERS)

target_link_libraries(${DEPNAME} libpng jpeg)

# this is needed because the headers for these deps are only copied as part of
# the shared build
add_dependencies(${DEPNAME}_static libpng jpeg)

set(TARGET_COMPILE_FLAGS
    SILLY_HAVE_JPG;SILLY_HAVE_PNG
    $<$<CONFIG:Debug>:SILLY_OPT_DEBUG>)

set_target_properties(${DEPNAME} PROPERTIES
    COMPILE_DEFINITIONS "${TARGET_COMPILE_FLAGS}")
    
set(TARGET_COMPILE_FLAGS
    SILLY_STATIC;SILLY_HAVE_JPG;SILLY_HAVE_PNG
    $<$<CONFIG:Debug>:SILLY_OPT_DEBUG>)

set_target_properties(${DEPNAME}_static PROPERTIES
    COMPILE_DEFINITIONS "${TARGET_COMPILE_FLAGS}")

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/../include/"
                                                   "${CMAKE_BINARY_DIR}/dependencies/include")

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../COPYING"
                                                    "${CMAKE_BINARY_DIR}/dependencies/SILLY-license.txt")

