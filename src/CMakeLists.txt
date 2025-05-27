
file(GLOB_RECURSE DYNAPOSE_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/DynaposeAPI/*.h"
)

file(GLOB_RECURSE DYNAPOSE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/ImplDynaposeAPI/*.cpp"
)

add_library(DynaPoseLib SHARED
        ${DYNAPOSE_HEADERS}
        ${DYNAPOSE_SOURCES}
)

target_include_directories(DynaPoseLib PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/DynaposeAPI
        ${CMAKE_SOURCE_DIR}/external/gltf
)

target_precompile_headers(DynaPoseLib PRIVATE
        PCH.h
)


