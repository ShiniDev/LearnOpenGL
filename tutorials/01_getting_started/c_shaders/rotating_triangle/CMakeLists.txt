add_executable(
    rotating_triangle
    main.cpp
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/triangle.fs.glsl
    ${CMAKE_CURRENT_BINARY_DIR}/triangle.fs.glsl
    COPYONLY
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/triangle.vs.glsl
    ${CMAKE_CURRENT_BINARY_DIR}/triangle.vs.glsl
    COPYONLY
)

target_link_libraries(rotating_triangle glad glfw my-utils my-wrappers)