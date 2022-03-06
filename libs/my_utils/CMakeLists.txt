add_library(
    my-utils
    INTERFACE
)

target_link_libraries(my-utils INTERFACE glad glfw)

target_include_directories(my-utils INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")