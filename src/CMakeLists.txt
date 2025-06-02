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
        "${CMAKE_CURRENT_SOURCE_DIR}/ImplTinyGLTF.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ImplDynaposeEngine/Core/ECS/Systems/ISystem.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ImplDynaposeEngine/Core/ECS/Components/Transform.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ImplDynaposeEngine/Core/ECS/Components/TransformUtils.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ImplDynaposeEngine/Core/ECS/Systems/UpdateTransformMatrices.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ImplDynaposeEngine/Core/World.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ImplDynaposeEngine/Rigs/Rig.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ImplDynaposeEngine/SceneDefinition/DynaPoseScene.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ImplDynaposeEngine/SceneDefinition/DynaPoseSceneManager.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ImplDynaposeEngine/Serialization/Serializers/TransformSerializer.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ImplDynaposeEngine/Serialization/DynaPoseSerialization.cpp"
        #${DYNAPOSE_SOURCES}
)

target_include_directories(DynaPoseLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/DynaposeEngine
)

target_precompile_headers(DynaPoseLib PRIVATE
        PCH.h
)

target_link_libraries(DynaPoseLib PRIVATE glm::glm)




