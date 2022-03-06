add_executable(
    b_hello_triangle
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


#add_custom_command(
#        TARGET b_hello_triangle PRE_BUILD 
#        COMMAND ${CMAKE_COMMAND} -E copy
#                ${CMAKE_CURRENT_SOURCE_DIR}/triangle.vs
#                ${CMAKE_CURRENT_BINARY_DIR})
#
target_link_libraries(b_hello_triangle glad glfw my-utils my-wrappers)

add_subdirectory(exercise_1)
add_subdirectory(exercise_2)
add_subdirectory(exercise_3)
add_subdirectory(my_diamond)