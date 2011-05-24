set(DEPNAME D3DX11Effects)

set(DXSDK_DIR $ENV{DXSDK_DIR})
string(REPLACE "\\" "/" DXSDK_DIR "${DXSDK_DIR}")

set(SOURCEDIR "${DXSDK_DIR}/Samples/C++/Effects11")

file(GLOB SOURCES
	"${SOURCEDIR}/*.cpp"
	"${SOURCEDIR}/*.inl")

set(HEADERS d3dx11effect.h)

include_directories(
    "${DXSDK_DIR}/include"
	"${SOURCEDIR}/Inc"
	"${SOURCEDIR}/Binary"
)

# This is not ideal, we should do something better than this!
link_directories(
    "${DXSDK_DIR}/Lib/x86"
)

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
                       COMMAND ${CMAKE_COMMAND} -E copy "${SOURCEDIR}/Inc/${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()

