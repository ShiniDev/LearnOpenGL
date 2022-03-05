add_library(
    my-wrappers
    shader.cpp
    shader.h
    shader_program.cpp
    shader_program.h
)

target_link_libraries(my-wrappers glad glfw my-utils)
target_include_directories(my-wrappers PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")