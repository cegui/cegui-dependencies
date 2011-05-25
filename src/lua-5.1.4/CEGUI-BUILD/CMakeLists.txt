set(DEPNAME lua)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../src/*.c")
list(REMOVE_ITEM SOURCES ../src/lua.c ../src/luac.c ../src/print.c)

set(HEADERS lua.h luaconf.h lualib.h lauxlib.h)

include_directories(../src)

cegui_add_library(${DEPNAME} SOURCES NONE)

if (WIN32)
    set_target_properties(${DEPNAME} PROPERTIES
        DEFINE_SYMBOL LUA_BUILD_AS_DLL)
endif()

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../src/${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../COPYRIGHT"
                                                    "${CMAKE_BINARY_DIR}/dependencies/lua-license.txt")

