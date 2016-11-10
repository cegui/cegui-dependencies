set(DEPNAME raqm)

set(PRIVATE_HEADERS
    ../src/raqm.h)

set(PUBLIC_HEADERS
    ../src/raqm.h)

 set(HEADERS
    ${PRIVATE_HEADERS}
    ${PUBLIC_HEADERS})
    
 set(SOURCES
    ../src/raqm.c)
    
    
if(MSVC)
    add_definitions(/wd4996 /wd4800)
endif()

include_directories(
  ../src
  ${CMAKE_BINARY_DIR}/dependencies/include
  ${CMAKE_BINARY_DIR}/dependencies/include/fribidi/lib
  ${CMAKE_BINARY_DIR}/dependencies/include/fribidi/charset  
  ${CMAKE_BINARY_DIR}/dependencies/include/harfbuzz/src
)

cegui_add_library(${DEPNAME} SOURCES HEADERS)


target_link_libraries(${DEPNAME} freetype harfbuzz fribidi)
add_dependencies(${DEPNAME}_static freetype harfbuzz fribidi)
target_link_libraries(${DEPNAME}_static freetype harfbuzz fribidi)

set(TARGET_COMPILE_FLAGS
    RAQM_EXPORTS
)

set(TARGET_COMPILE_FLAGS_STATIC
    RAQM_STATIC
    RAQM_EXPORTS
)


set_target_properties(${DEPNAME} PROPERTIES
    COMPILE_DEFINITIONS "${TARGET_COMPILE_FLAGS}")

set_target_properties(${DEPNAME}_static PROPERTIES
    COMPILE_DEFINITIONS "${TARGET_COMPILE_FLAGS_STATIC}")
    
foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/dependencies/include/libraqm/src/${_H_FILE}")
endforeach()                                

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../COPYING"
                                                    "${CMAKE_BINARY_DIR}/dependencies/libraqm-license.txt")
                                                    
#Files end with .c so cmake can't decide what the hell this is
set_target_properties(${DEPNAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${DEPNAME}_static PROPERTIES LINKER_LANGUAGE CXX)