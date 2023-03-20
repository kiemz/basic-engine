cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

project(basic-engine)

# Add.lib files
link_directories(./library)

# Add.include files
include_directories(./include)

# STB_IMAGE
add_library(stb_image "thirdparty/stb_image.cpp")

# GLAD
add_library(glad "thirdparty/glad.c")

add_executable(basic-engine "source/main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET basic-engine PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(basic-engine glfw3 opengl32 glad stb_image)
target_include_directories(basic-engine PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
)