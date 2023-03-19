cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

project("basic-engine")

# Add.lib files
link_directories(./library)

# Add.include files
include_directories(./include)

# GLAD
add_library(glad "thirdparty/glad.c")

add_executable(basic-engine "source/main.cpp")
target_link_libraries(basic-engine glfw3 opengl32 glad)
target_include_directories(basic-engine PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
)