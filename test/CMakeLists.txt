include(FetchContent)
FetchContent_Declare(
        glm
        GIT_REPOSITORY	https://github.com/g-truc/glm.git
        GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e
)

FetchContent_MakeAvailable(glm)


FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(DynaPoseTests
        TestDynaPoseSerialization.cpp
)

target_link_libraries(DynaPoseTests PRIVATE
    GTest::gtest_main
    DynaPoseLib
    glm::glm
)

add_test(
        NAME TestDeserialization
        COMMAND DynaPoseTests
)

set_tests_properties(TestDeserialization PROPERTIES
    ENVIRONMENT "RESOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/TestFiles"
)

add_custom_command(TARGET DynaPoseTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:DynaPoseLib>
        $<TARGET_FILE_DIR:DynaPoseTests>
)
