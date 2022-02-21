cmake_minimum_required(VERSION 3.21.3)  #cmake 最小版本

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(IMGUI_SOURCE_DIR ${PROJECT_SOURCE_DIR}/thirdParty/imgui)
set(IMGUI_SOURCE 
    ${IMGUI_SOURCE_DIR}/imgui.cpp 
    ${IMGUI_SOURCE_DIR}/imgui_widgets.cpp 
    ${IMGUI_SOURCE_DIR}/imgui_draw.cpp
    ${IMGUI_SOURCE_DIR}/imgui_tables.cpp
)
set(IMGUI_INCLUDE 
    ${PROJECT_SOURCE_DIR}/thirdParty/imgui
    ${PROJECT_SOURCE_DIR}/thirdParty/imgui/backends
)

add_library(mylib
    interactive.cpp
    texture.cpp
    transform.cpp
    mrp.cpp
    object.cpp
    shaderV2.cpp
    cam.cpp
    data.cpp
    model.cpp
    mesh.cpp
    material.cpp
    ui.cpp
    light.cpp
    animation.cpp
    ${IMGUI_SOURCE}
)

target_link_libraries(mylib
    PUBLIC assimp
)


target_include_directories(mylib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/thirdParty/glm
        ${IMGUI_INCLUDE}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/thirdParty/stb
        ${GLAD_OUT_DIR}/include
)

#message("project binary dir:" ${PROJECT_BINARY_DIR})        #项目的build目录
#message("current binary dir: " ${CMAKE_CURRENT_BINARY_DIR})     #当前cmakelists的工作目录
#message("binary dir: " ${CMAKE_BINARY_DIR})     # 项目的build目录
