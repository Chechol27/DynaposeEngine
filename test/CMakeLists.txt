include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(DynaPoseTests ${TEST_SOURCES})

target_link_libraries(DynaPoseTests
    GTest::gtest_main
    DynaPoseLib
)

include(GoogleTest)
gtest_discover_tests(DynaPoseTests)