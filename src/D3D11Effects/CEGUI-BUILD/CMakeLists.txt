set(DEPNAME D3DX11Effects)

file(GLOB SOURCES
	"../*.cpp"
	"../*.inl")

set(HEADERS d3dx11effect.h)
if( MINGW )
    list( APPEND HEADERS d3d11-effects-mingw-supplements.h )
endif()

include_directories(
	"../Inc"
	"../Binary"
)

if( MSVC )
    set(DXSDK_DIR $ENV{DXSDK_DIR})
    string(REPLACE "\\" "/" DXSDK_DIR "${DXSDK_DIR}")
    include_directories( "${DXSDK_DIR}/Include" )
endif()

#
# This doesn't really build as a DLL, and since I am not happy to distribute the
# source, we can't customise it to build how we want as we might do with the
# freely licensed libs that make up this dependencies package.  As such we
# create a static lib for both dynamic and static output dirs (we could have
# copied a single lib, but getting the name is just as much a hack as doing
# what we have here).
#
add_library(${DEPNAME} STATIC ${SOURCES})

set_target_properties(${DEPNAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/dependencies/lib/dynamic"
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/dependencies/lib/dynamic"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/dependencies/lib/dynamic"
    ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/dependencies/lib/dynamic"
    ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/dependencies/lib/dynamic"

    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/dependencies/lib/dynamic"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/dependencies/lib/dynamic"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/dependencies/lib/dynamic"
    LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/dependencies/lib/dynamic"
    LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/dependencies/lib/dynamic"

    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/dependencies/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/dependencies/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/dependencies/bin"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/dependencies/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/dependencies/bin")

set_target_properties(${DEPNAME} PROPERTIES
    COMPILE_DEFINITIONS "FXDPF")

add_library(${DEPNAME}_static STATIC ${SOURCES})

set_target_properties(${DEPNAME}_static PROPERTIES
    ARCHIVE_OUTPUT_NAME ${DEPNAME}
    LIBRARY_OUTPUT_NAME ${DEPNAME}
    RUNTIME_OUTPUT_NAME ${DEPNAME}

    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/dependencies/lib/static"
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/dependencies/lib/static"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/dependencies/lib/static"
    ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/dependencies/lib/static"
    ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/dependencies/lib/static"

    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/dependencies/lib/static"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/dependencies/lib/static"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/dependencies/lib/static"
    LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/dependencies/lib/static"
    LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/dependencies/lib/static"

    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/dependencies/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/dependencies/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/dependencies/bin"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/dependencies/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/dependencies/bin")

set_target_properties(${DEPNAME}_static PROPERTIES
    COMPILE_DEFINITIONS "FXDPF")

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../Inc/${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../directx-sdk-license.rtf"
                                                    "${CMAKE_BINARY_DIR}/dependencies/directx-sdk-license.rtf")