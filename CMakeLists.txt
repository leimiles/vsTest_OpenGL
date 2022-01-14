cmake_minimum_required(VERSION 3.10.0)  #cmake 最小版本

project(MDV VERSION 0.1) #工程当前版本

configure_file(MDVConfig.h.in MDVConfig.h)  #工程版本配置文件

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/mdv" CACHE PATH "..." FORCE)        #设置安装目录

set(EXE_NAME mdv)   #设置可执行程序的名称
set(INCLUDE include)    #设置包含头文件的目录, 本项目

set(TEXTURE_TARGET_DIR "${CMAKE_CURRENT_BINARY_DIR}/resources")     #图片资源目标目录
set(TEXTURE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/resources/textures")    #图片资源源目录
file(COPY ${TEXTURE_SOURCE_DIR} DESTINATION ${TEXTURE_TARGET_DIR})

set(TEXTURE_TARGET_DIR "${CMAKE_CURRENT_BINARY_DIR}/resources")     #着色器资源目标目录
set(TEXTURE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/resources/shaders")    #着色器资源源目录
file(COPY ${TEXTURE_SOURCE_DIR} DESTINATION ${TEXTURE_TARGET_DIR})

include_directories(${INCLUDE}) #构建时包含头文件的路径位置

add_subdirectory(src)       #构建时包含 src 路径下的内容, src 下构建的内容才能被找到

#link_directories(lib) #使用编译好的库，需要在 add_executable 执行之前，指定编译好的库所在的位置

add_executable(${EXE_NAME} main.cpp)    #构建可执行程序，其源码为 main.cpp

set_property(TARGET ${EXE_NAME} PROPERTY CXX_STANDARD 17)

target_include_directories(${EXE_NAME} PUBLIC ${PROJECT_BINARY_DIR})    #构建时包含二进制文件目录, 没有这会使得 MDVConfig.h 找不到

# DOWNLOAD ALL THE SUBMODULES   下载所有子模块
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")

# Update submodules as needed   更新子模块
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMODE_RESULT}, please check")
        endif()
    endif()
endif()

# CHECK ALL THE SUBMODULES  检查子模块
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/thirdParty/glfw/CMakeLists.txt")
    message(FATAL_ERROR "the glfw submodules was not downloaded!")
endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/thirdParty/glm/CMakeLists.txt")
    message(FATAL_ERROR "the glm submodules was not downloaded!")
endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/thirdParty/glad/CMakeLists.txt")
    message(FATAL_ERROR "the glad submodules was not downloaded!")
endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/thirdParty/stb/stb_image.h")
    message(FATAL_ERROR "the stb submodules was not downloaded!")
endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/thirdParty/assimp/CMakeLists.txt")
    message(FATAL_ERROR "the assimp submodules was not downloaded!")
endif()

add_subdirectory(thirdParty/glfw)   #构建时包含第三方库下的 glfw 文件夹，若文件夹内包含 CMakeLists.txt 文件，则会执行
add_subdirectory(thirdParty/assimp)   #构建时包含第三方库下的 assimp 文件夹，若文件夹内包含 CMakeLists.txt 文件，则会执行
add_subdirectory(thirdParty/glad)   #构建时包含第三方库下的 glad 文件夹，若文件夹内包含 CMakeLists.txt 文件，则会执行
target_link_libraries(${EXE_NAME} glfw glad mylib)    #构建时链接指定的库

install(TARGETS ${EXE_NAME} DESTINATION ./)        #安装在项目目录的 mdv 文件夹下
install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources DESTINATION ./)    #安装在项目目录的 mdv 文件夹下