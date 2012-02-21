################################################################################
# IL library
################################################################################
file(GLOB IL_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "../src-IL/src/*.c"
    "../src-IL/src/*.cpp")

include_directories(
	"../include"
	"../src-IL/include"
    ${CMAKE_BINARY_DIR}/dependencies/include)

cegui_add_library(IL IL_SOURCES NONE)

if(WIN32)
    set_target_properties(IL PROPERTIES
        COMPILE_DEFINITIONS "PNG_DLL;MNG_DLL")
endif()

target_link_libraries(IL libpng libmng libtiff jpeg)

# this is needed because the headers for these deps are only copied as part of
# the shared build
add_dependencies(IL_static libpng libmng libtiff jpeg)

set_target_properties(IL_static PROPERTIES
    COMPILE_DEFINITIONS IL_STATIC_LIB)

################################################################################
# ILU library
################################################################################
file(GLOB ILU_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "../src-ILU/src/*.c"
    "../src-ILU/src/*.cpp")

include_directories(
	"../src-ILU/include")

cegui_add_library(ILU ILU_SOURCES NONE)

target_link_libraries(ILU IL)

set_target_properties(ILU_static PROPERTIES
    COMPILE_DEFINITIONS IL_STATIC_LIB)

add_custom_command(TARGET IL POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/../include/IL"
                                                   "${CMAKE_BINARY_DIR}/dependencies/include/IL")

add_custom_command(TARGET IL POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../COPYING"
                                                    "${CMAKE_BINARY_DIR}/dependencies/devil-license.txt")

