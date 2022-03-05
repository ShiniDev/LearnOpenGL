add_library(
    glad
    glad/glad/glad.h
    glad/KHR/khrplatform.h
    glad/glad.c
)

target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/glad")

add_subdirectory(glfw)
add_subdirectory(my_utils)