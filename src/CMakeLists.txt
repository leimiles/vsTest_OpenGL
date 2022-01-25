cmake_minimum_required(VERSION 3.21.3)  #cmake 最小版本

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(mylib
    interactive.cpp
    texture.cpp
    transform.cpp
    mrp.cpp
    geometry.cpp
    object.cpp
    shader.cpp
    cam.cpp
    data.cpp
    model.cpp
    mesh.cpp
    material.cpp
)

target_link_libraries(mylib
    PUBLIC assimp
)


target_include_directories(mylib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/thirdParty/glm
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/thirdParty/stb
        ${GLAD_OUT_DIR}/include
)

#message("project binary dir:" ${PROJECT_BINARY_DIR})        #项目的build目录
#message("current binary dir: " ${CMAKE_CURRENT_BINARY_DIR})     #当前cmakelists的工作目录
#message("binary dir: " ${CMAKE_BINARY_DIR})     # 项目的build目录
