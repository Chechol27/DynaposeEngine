cmake_minimum_required(VERSION 3.31)
project(DynaPoseLib)

set(CMAKE_CXX_STANDARD 23)

include_directories(
        external/gltf
        external/spdlog
)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()


