cmake_minimum_required(VERSION 3.16)

set (CMAKE_CXX_STANDARD 17)

project(VanGogh)
if(Boost_FOUND)
include_directories(${Boost_INCLUDE_DIRS}) 
endif()
include_directories( ${PROJECT_SOURCE_DIR}/includes )
add_executable(VanGogh stb_image/stb_image.cpp Shader.h glad.c VanGogh.cpp)

target_link_libraries(VanGogh GL dl glfw)
