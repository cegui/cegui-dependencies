set(DEPNAME glm)
add_custom_target(${DEPNAME})

file(GLOB_RECURSE HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/.." ../glm/*.hpp ../glm/*.inl ../glm/*.cpp)

foreach(_H_FILE ${HEADERS})
add_custom_command(TARGET ${DEPNAME}  
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../${_H_FILE}"
                                         "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()

add_custom_command(TARGET ${DEPNAME}  
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../copying.txt"
                                                    "${CMAKE_BINARY_DIR}/dependencies/glm-copying.txt")

