cmake_minimum_required(VERSION 2.8)
include(CMakeDependentOption)

project(CEGUI-DEPS)

set(CMAKE_DEBUG_POSTFIX _d)

cmake_dependent_option( CEGUI_MSVC_STATIC_RUNTIME "Specifies whether to the static runtime (/MT and /MTd) or the DLL runtime (/MD and /MDd)." FALSE "MSVC" FALSE )

if (CEGUI_MSVC_STATIC_RUNTIME)
    foreach(_BUILD_CONFIG DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
        foreach(_BUILD_VARS CMAKE_CXX_FLAGS_${_BUILD_CONFIG} CMAKE_C_FLAGS_${_BUILD_CONFIG})
            string(REGEX REPLACE /MD /MT ${_BUILD_VARS} ${${_BUILD_VARS}})
        endforeach()
    endforeach()
endif()

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()


macro(cegui_add_library _NAME _SOURCES_VAR _HEADERS_VAR)
    add_library(${_NAME} SHARED ${${_SOURCES_VAR}} ${${_HEADERS_VAR}})

    set_target_properties(${_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/dynamic"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib/dynamic"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib/dynamic"
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/lib/dynamic"
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/lib/dynamic"

        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/dynamic"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib/dynamic"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib/dynamic"
        LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/lib/dynamic"
        LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/lib/dynamic"

        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin")


    add_library(${_NAME}_static STATIC ${${_SOURCES_VAR}} ${${_HEADERS_VAR}})

    set_target_properties(${_NAME}_static PROPERTIES
        ARCHIVE_OUTPUT_NAME ${_NAME}
        LIBRARY_OUTPUT_NAME ${_NAME}
        RUNTIME_OUTPUT_NAME ${_NAME}

        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/static"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib/static"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib/static"
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/lib/static"
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/lib/static"

        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/static"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib/static"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib/static"
        LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/lib/static"
        LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/lib/static"

        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin")

endmacro()

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/include")

add_subdirectory(src/zlib-1.2.5/CEGUI-BUILD)
add_subdirectory(src/libpng-1.4.7/CEGUI-BUILD)
add_subdirectory(src/jpeg-8c/CEGUI-BUILD)
add_subdirectory(src/libmng-1.0.10/CEGUI-BUILD)
add_subdirectory(src/tiff-3.9.5/CEGUI-BUILD)

add_subdirectory(src/freetype-2.4.4/CEGUI-BUILD)
add_subdirectory(src/pcre-8.12/CEGUI-BUILD)

add_subdirectory(src/lua-5.1.4/CEGUI-BUILD)

add_subdirectory(src/expat-2.0.1/CEGUI-BUILD)
add_subdirectory(src/xerces-c-3.1.1/CEGUI-BUILD)

add_subdirectory(src/SILLY/CEGUI-BUILD)
add_subdirectory(src/FreeImage-3.15.0/CEGUI-BUILD)
add_subdirectory(src/corona-1.0.2/CEGUI-BUILD)
add_subdirectory(src/devil-1.7.8/CEGUI-BUILD)

add_subdirectory(src/freeglut-2.6.0/CEGUI-BUILD)

