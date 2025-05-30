cmake_minimum_required(VERSION 3.31)
project(DynaPoseLib)

set(CMAKE_CXX_STANDARD 23)

include_directories(
        external/gltf
        external/spdlog/include
        ${CMAKE_BINARY_DIR}/_deps/glm-src/glm
)

add_subdirectory(src)
add_subdirectory(test)

