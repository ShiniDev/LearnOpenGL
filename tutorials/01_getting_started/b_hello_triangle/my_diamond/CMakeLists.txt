add_executable(
    my_diamond
    main.cpp
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/diamond.fs.glsl
    ${CMAKE_CURRENT_BINARY_DIR}/diamond.fs.glsl
    COPYONLY
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/diamond.vs.glsl
    ${CMAKE_CURRENT_BINARY_DIR}/diamond.vs.glsl
    COPYONLY
)

target_link_libraries(my_diamond glad glfw my-utils my-wrappers)