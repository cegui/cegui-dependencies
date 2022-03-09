file(GLOB_RECURSE UNWANTED 
    ${CMAKE_BINARY_DIR}/dependencies/*manifest*
    ${CMAKE_BINARY_DIR}/dependencies/bin/*.txt
    ${CMAKE_BINARY_DIR}/dependencies/*.ilk
    ${CMAKE_BINARY_DIR}/dependencies/*.in
    ${CMAKE_BINARY_DIR}/dependencies/Makefile*)

if (UNWANTED)
    file(REMOVE ${UNWANTED})
endif()

