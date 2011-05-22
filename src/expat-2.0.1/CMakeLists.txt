set(DEPNAME expat)

set(SOURCES lib/libexpat.def lib/xmlrole.c lib/xmltok.c lib/xmlparse.c)
set(HEADERS lib/expat.h lib/expat_external.h)

add_definitions(-DCOMPILED_FROM_DSP)

cegui_add_library(${DEPNAME} SOURCES HEADERS)


set_target_properties(${DEPNAME} PROPERTIES
    DEFINE_SYMBOL EXPAT_EXPORTS)

