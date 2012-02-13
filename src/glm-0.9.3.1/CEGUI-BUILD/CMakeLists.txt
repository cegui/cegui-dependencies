set(DEPNAME glm)

file(GLOB_RECURSE HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/.." ../glm/*.hpp ../glm/*.inl ../glm/*.cpp)

set(OUT_FILES "${CMAKE_BINARY_DIR}/dependencies/glm-copying.txt")

foreach(_H_FILE ${HEADERS})
    list(APPEND OUT_FILES "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()

add_custom_target(${DEPNAME} ALL DEPENDS ${OUT_FILES})

foreach(_H_FILE ${HEADERS})
    add_custom_command(OUTPUT "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../${_H_FILE}"
                                         "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()

add_custom_command(OUTPUT "${CMAKE_BINARY_DIR}/dependencies/glm-copying.txt" 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../copying.txt"
                                                    "${CMAKE_BINARY_DIR}/dependencies/glm-copying.txt")

