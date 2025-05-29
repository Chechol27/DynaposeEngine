include(FetchContent)

FetchContent_Declare(
        glm
        GIT_REPOSITORY	https://github.com/g-truc/glm.git
        GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e
)

FetchContent_MakeAvailable(glm)


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
        ${CMAKE_CURRENT_SOURCE_DIR}/DynaposeEngine
        ${CMAKE_BINARY_DIR}/_deps/glm-src/glm
)

target_precompile_headers(DynaPoseLib PRIVATE
        PCH.h
)

target_link_libraries(DynaPoseLib PRIVATE glm::glm)




