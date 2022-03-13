set(DEPNAME pugixml)

set(PUGIXML_VERSION_MAJOR 1) 
set(PUGIXML_VERSION_MINOR 12) 
set(PUGIXML_VERSION_MICRO 1) 
set(PUGIXML_VERSION "${PUGIXML_VERSION_MAJOR}.${PUGIXML_VERSION_MINOR}.${PUGIXML_VERSION_MICRO}")

set(HEADERS ../src/pugiconfig.hpp ../src/pugixml.hpp)
set(SOURCES ../src/pugixml.cpp)
if (WIN32)
    list(APPEND SOURCES ../scripts/pugixml_dll.rc)
endif()

foreach(_H_FILE ${HEADERS})
    # From CMake 3.20:
    #cmake_path(RELATIVE_PATH ${_H_FILE} "${CMAKE_CURRENT_SOURCE_DIR}/../src")
    get_filename_component(_H_FILE "${_H_FILE}" ABSOLUTE)
    file(RELATIVE_PATH _H_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../src" ${_H_FILE})
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../src/${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}" COPYONLY)
endforeach()                                

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE.md" "${CMAKE_BINARY_DIR}/dependencies/pugixml-license.txt" COPYONLY)

cegui_add_library(${DEPNAME} SOURCES HEADERS)

if (MSVC AND TARGET ${DEPNAME})
    target_compile_definitions(${DEPNAME} PUBLIC "PUGIXML_API=__declspec(dllexport)")
endif()

get_property(ALL_TARGETS DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY BUILDSYSTEM_TARGETS)
foreach(TARGET_NAME IN LISTS ALL_TARGETS)

    target_include_directories(${TARGET_NAME}
        PUBLIC
            ${CMAKE_BINARY_DIR}/dependencies/include
        PRIVATE
            ../src
    )
    target_compile_definitions(${TARGET_NAME} PUBLIC "PUGIXML_NO_EXCEPTIONS" "PUGIXML_NO_XPATH")    
    set_target_properties(${TARGET_NAME} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
        POSITION_INDEPENDENT_CODE ON
        SOVERSION ${PUGIXML_VERSION_MAJOR}
        VERSION ${PUGIXML_VERSION})

endforeach()
