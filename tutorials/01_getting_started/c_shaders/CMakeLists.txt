add_executable(
    c_shaders
    main.cpp
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders.fs.glsl
    ${CMAKE_CURRENT_BINARY_DIR}/shaders.fs.glsl
    COPYONLY
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders.vs.glsl
    ${CMAKE_CURRENT_BINARY_DIR}/shaders.vs.glsl
    COPYONLY
)

target_link_libraries(c_shaders glad glfw my-utils my-wrappers)
add_subdirectory(rotating_triangle)