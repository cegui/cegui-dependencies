set(DEPNAME HARFBUZZ)

set(PRIVATE_HEADERS
    ../src/hb-atomic-private.hh 
    ../src/hb-buffer-deserialize-json.hh 
    ../src/hb-buffer-deserialize-text.hh 
    ../src/hb-buffer-private.hh 
    ../src/hb-cache-private.hh 
    ../src/hb-face-private.hh 
    ../src/hb-font-private.hh 
    ../src/hb-mutex-private.hh 
    ../src/hb-object-private.hh 
    ../src/hb-open-file-private.hh 
    ../src/hb-open-type-private.hh 
    ../src/hb-ot-cmap-table.hh 
    ../src/hb-ot-glyf-table.hh 
    ../src/hb-ot-head-table.hh 
    ../src/hb-ot-hhea-table.hh 
    ../src/hb-ot-hmtx-table.hh 
    ../src/hb-ot-maxp-table.hh 
    ../src/hb-ot-name-table.hh 
    ../src/hb-ot-os2-table.hh 
    ../src/hb-ot-post-table.hh 
    ../src/hb-private.hh 
    ../src/hb-set-private.hh 
    ../src/hb-shape-plan-private.hh 
    ../src/hb-shaper-list.hh 
    ../src/hb-shaper-impl-private.hh 
    ../src/hb-shaper-private.hh 
    ../src/hb-unicode-private.hh 
    ../src/hb-utf-private.hh
    
    ../src/hb-ot-layout-common-private.hh 
    ../src/hb-ot-layout-gdef-table.hh 
    ../src/hb-ot-layout-gpos-table.hh 
    ../src/hb-ot-layout-gsubgpos-private.hh 
    ../src/hb-ot-layout-gsub-table.hh 
    ../src/hb-ot-layout-jstf-table.hh 
    ../src/hb-ot-layout-private.hh 
    ../src/hb-ot-map-private.hh 
    ../src/hb-ot-shape-complex-arabic-fallback.hh 
    ../src/hb-ot-shape-complex-arabic-private.hh 
    ../src/hb-ot-shape-complex-arabic-table.hh 
    ../src/hb-ot-shape-complex-arabic-win1256.hh 
    ../src/hb-ot-shape-complex-indic-machine.hh 
    ../src/hb-ot-shape-complex-indic-private.hh 
    ../src/hb-ot-shape-complex-myanmar-machine.hh 
    ../src/hb-ot-shape-complex-private.hh 
    ../src/hb-ot-shape-normalize-private.hh 
    ../src/hb-ot-shape-fallback-private.hh 
    ../src/hb-ot-shape-private.hh 
    ../src/hb-ot-shape-complex-use-machine.hh 
    ../src/hb-ot-shape-complex-use-private.hh)    
    
set(PUBLIC_HEADERS
    ../config.h
    
    ../src/hb.h   
    ../src/hb-blob.h   
    ../src/hb-buffer.h   
    ../src/hb-common.h   
    ../src/hb-deprecated.h   
    ../src/hb-face.h   
    ../src/hb-font.h   
    ../src/hb-set.h   
    ../src/hb-shape.h   
    ../src/hb-shape-plan.h   
    ../src/hb-unicode.h   

    ../src/hb-version.h
    
    ../src/hb-ot.h 
    ../src/hb-ot-font.h 
    ../src/hb-ot-layout.h 
    ../src/hb-ot-shape.h 
    ../src/hb-ot-tag.h
    
    ../src/hb-ft.h
    
    ../src/hb-ucdn/ucdn.h
    ../src/hb-ucdn/unicodedata_db.h
    
    ../src/hb-uniscribe.h)
    
 set(HEADERS
    ${PRIVATE_HEADERS}
    ${PUBLIC_HEADERS})
    
 set(SOURCES 
    ../src/hb-set.cc
    ../src/hb-shape.cc
    ../src/hb-shape-plan.cc
    ../src/hb-unicode.cc
    ../src/hb-shaper.cc
    ../src/hb-warning.cc
    ../src/hb-face.cc
    ../src/hb-font.cc
    ../src/hb-common.cc
    ../src/hb-buffer.cc
    ../src/hb-blob.cc
    ../src/hb-buffer-serialize.cc
    ../src/hb-ot-tag.cc
    
    ../src/hb-fallback-shape.cc
    
    ../src/hb-ot-shape-complex-default.cc 
    ../src/hb-ot-shape-complex-hangul.cc 
    ../src/hb-ot-shape-complex-hebrew.cc 
    ../src/hb-ot-shape-complex-indic.cc 
    ../src/hb-ot-shape-complex-indic-table.cc 
    ../src/hb-ot-shape-complex-myanmar.cc 
    ../src/hb-ot-shape-complex-thai.cc 
    ../src/hb-ot-shape-complex-tibetan.cc 
    ../src/hb-ot-shape-complex-use.cc 
    ../src/hb-ot-shape-normalize.cc 
    ../src/hb-ot-shape-fallback.cc 
    ../src/hb-ot-shape-complex-use-table.cc 
    ../src/hb-ot-map.cc
    ../src/hb-ot-shape.cc  
    ../src/hb-ot-shape-complex-arabic.cc
    ../src/hb-ot-font.cc 
    ../src/hb-ot-layout.cc
    
    ../src/hb-ft.cc
    
    ../src/hb-ucdn/ucdn.c
    
    ../src/hb-ucdn.cc
      
    ../src/hb-uniscribe.cc)


if(MSVC)
    add_definitions(/wd4996 /wd4800)
endif()

include_directories(
  ../
  ../src
  ../src/hb-ucdn
  ${CMAKE_BINARY_DIR}/dependencies/include
)

cegui_add_library(${DEPNAME} SOURCES HEADERS)


target_link_libraries(${DEPNAME} freetype usp10 gdi32 rpcrt4)
add_dependencies(${DEPNAME}_static freetype)
target_link_libraries(${DEPNAME}_static usp10 gdi32 rpcrt4)

set(TARGET_COMPILE_FLAGS
    HAVE_CONFIG_H
)

set(TARGET_COMPILE_FLAGS_STATIC
    HAVE_CONFIG_H
    HB_STATIC
)


set_target_properties(${DEPNAME} PROPERTIES
    COMPILE_DEFINITIONS "${TARGET_COMPILE_FLAGS}")

set_target_properties(${DEPNAME}_static PROPERTIES
    COMPILE_DEFINITIONS "${TARGET_COMPILE_FLAGS_STATIC}")
    
foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${_H_FILE}"
                                                        "${CMAKE_BINARY_DIR}/dependencies/include/harfbuzz/src/${_H_FILE}")
endforeach()                                

add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../COPYING"
                                                    "${CMAKE_BINARY_DIR}/dependencies/harfbuzz-license.txt")

#Files end with .cc so cmake can't decide what the hell this is
set_target_properties(${DEPNAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${DEPNAME}_static PROPERTIES LINKER_LANGUAGE CXX)