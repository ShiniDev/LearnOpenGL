add_executable(
    b_hello_triangle_exercise_2
    main.cpp
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/triangle_fs.glsl
    ${CMAKE_CURRENT_BINARY_DIR}/triangle_fs.glsl
    COPYONLY
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/triangle_vs.glsl
    ${CMAKE_CURRENT_BINARY_DIR}/triangle_vs.glsl
    COPYONLY
)

target_link_libraries(b_hello_triangle_exercise_2 glad glfw my-utils my-wrappers)