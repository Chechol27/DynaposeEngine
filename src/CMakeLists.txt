
file(GLOB_RECURSE DYNAPOSE_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/DynaposeEngine/*.h"
)

file(GLOB_RECURSE DYNAPOSE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/ImplTinyGLTF.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ImplDynaposeEngine/*.cpp"
)

add_library(DynaPoseLib SHARED
        ${DYNAPOSE_HEADERS}
        ${DYNAPOSE_SOURCES}
)

target_include_directories(DynaPoseLib PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/DynaposeEngine
)

target_precompile_headers(DynaPoseLib PRIVATE
        PCH.h
)


