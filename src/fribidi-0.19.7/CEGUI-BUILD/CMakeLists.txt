set(DEPNAME fribidi)

set(SOURCES
  ../charset/fribidi-char-sets-cp1255.c
  ../charset/fribidi-char-sets-cp1256.c
  ../charset/fribidi-char-sets-iso8859-6.c
  ../charset/fribidi-char-sets-iso8859-8.c
  ../charset/fribidi-char-sets-utf8.c
  ../charset/fribidi-char-sets.c
  ../charset/fribidi-char-sets-cap-rtl.c
  
  ../lib/fribidi-mem.c
  ../lib/fribidi-mirroring.c
  ../lib/fribidi-run.c
  ../lib/fribidi-shape.c
  ../lib/fribidi.c
  ../lib/fribidi-arabic.c
  ../lib/fribidi-bidi.c
  ../lib/fribidi-bidi-types.c
  ../lib/fribidi-deprecated.c
  ../lib/fribidi-joining.c
  ../lib/fribidi-joining-types.c
)
  
set(HEADERS
  ../charset/fribidi-char-sets-iso8859-8.h
  ../charset/fribidi-char-sets-list.h
  ../charset/fribidi-char-sets-utf8.h
  ../charset/fribidi-char-sets.h
  ../charset/fribidi-char-sets-cap-rtl.h
  ../charset/fribidi-char-sets-cp1255.h
  ../charset/fribidi-char-sets-cp1256.h
  ../charset/fribidi-char-sets-iso8859-6.h
  ../lib/fribidi-shape.h
  ../lib/fribidi-types.h
  ../lib/fribidi-unicode.h
  ../lib/fribidi-unicode-version.h
  ../lib/joining-types.h
  ../lib/mem.h
  ../lib/run.h
  ../lib/bidi-types.h
  ../lib/common.h
  ../lib/config.h
  ../lib/debug.h
  ../lib/fribidi.h
  ../lib/fribidi-arabic.h
  ../lib/fribidi-begindecls.h
  ../lib/fribidi-bidi.h
  ../lib/fribidi-bidi-types.h
  ../lib/fribidi-bidi-types-list.h
  ../lib/fribidi-common.h
  ../lib/fribidi-config.h.in
  ../lib/fribidi-deprecated.h
  ../lib/fribidi-enddecls.h
  ../lib/fribidi-flags.h
  ../lib/fribidi-joining.h
  ../lib/fribidi-joining-types.h
  ../lib/fribidi-joining-types-list.h
  ../lib/fribidi-mirroring.h
  
  ../lib/fribidi-config.h
)

include_directories(
  ../lib
  ../charset
)

cegui_add_library(${DEPNAME} SOURCES HEADERS)

set_target_properties(${DEPNAME} PROPERTIES
    COMPILE_DEFINITIONS HAVE_CONFIG_H)

set_target_properties(${DEPNAME}_static PROPERTIES
    COMPILE_DEFINITIONS HAVE_CONFIG_H)

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/dependencies/include/fribidi/lib/${_H_FILE}")
endforeach()                                

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../COPYING"
                                                    "${CMAKE_BINARY_DIR}/dependencies/fribidi-license.txt")
