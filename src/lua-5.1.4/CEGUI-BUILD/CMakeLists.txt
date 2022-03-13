set(DEPNAME lua)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../src/*.c")
list(REMOVE_ITEM SOURCES ../src/lua.c ../src/luac.c ../src/print.c)

set(HEADERS ../src/lua.h ../src/luaconf.h ../src/lualib.h ../src/lauxlib.h)

foreach(_H_FILE ${HEADERS})
    # From CMake 3.20:
    #cmake_path(RELATIVE_PATH ${_H_FILE} "${CMAKE_CURRENT_SOURCE_DIR}/../src")
    get_filename_component(_H_FILE "${_H_FILE}" ABSOLUTE)
    file(RELATIVE_PATH _H_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../src" ${_H_FILE})
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../src/${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}" COPYONLY)
endforeach()                                

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../COPYRIGHT" "${CMAKE_BINARY_DIR}/dependencies/lua-license.txt" COPYONLY)

cegui_add_library(${DEPNAME} SOURCES NONE)

if (WIN32)
    set_target_properties(${DEPNAME} PROPERTIES DEFINE_SYMBOL LUA_BUILD_AS_DLL)
endif()

get_property(ALL_TARGETS DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY BUILDSYSTEM_TARGETS)
foreach(TARGET_NAME IN LISTS ALL_TARGETS)

    target_include_directories(${TARGET_NAME}
        PUBLIC
            ${CMAKE_BINARY_DIR}/dependencies/include
        PRIVATE
            ../src
    )

endforeach()
