set(IMGUI_LIB       imgui)
set(GLFW_LIB        glfw)
set(GLAD_LIB        glad)
set(IMPL_LIB        impl)
set(IMPLOT_LIB      implot)
set(JSON_LIB        json)

# imgui
add_library(${IMGUI_LIB}
    "imgui/imgui.cpp"
    "imgui/imgui_draw.cpp"
    "imgui/imgui_demo.cpp"
    "imgui/imgui_tables.cpp"
    "imgui/imgui_widgets.cpp")
target_include_directories(${IMGUI_LIB} PUBLIC "imgui")
target_set_warnings(TARGET ${IMGUI_LIB} ENABLE OFF AS_ERROR OFF)

# glad
add_library(${GLAD_LIB}
    "glad/src/glad.c")
target_include_directories(${GLAD_LIB} PUBLIC "glad/include")
target_link_libraries(${GLAD_LIB} PUBLIC ${IMGUI_LIB})
target_set_warnings(TARGET ${IMGUI_LIB} ENABLE OFF AS_ERROR OFF)

# glfw
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("glfw")
target_link_libraries(${GLFW_LIB} PUBLIC ${IMGUI_LIB})
target_set_warnings(TARGET ${IMGUI_LIB} ENABLE OFF AS_ERROR OFF)

# implot
add_library(${IMPLOT_LIB}
    "implot/implot_demo.cpp"
    "implot/implot_items.cpp"
    "implot/implot.cpp")
target_include_directories(${IMPLOT_LIB} PUBLIC "implot")
target_link_libraries(${IMPLOT_LIB} PUBLIC ${IMGUI_LIB})
target_set_warnings(TARGET ${IMPLOT_LIB} ENABLE OFF AS_ERROR OFF)

# json
add_library(${JSON_LIB} INTERFACE)
target_include_directories(${JSON_LIB} INTERFACE "json")
target_set_warnings(TARGET ${JSON_LIB} ENABLE OFF AS_ERROR OFF)

# impl
add_library(${IMPL_LIB}
    impl/imgui_impl_glfw.h
    impl/imgui_impl_glfw.cpp
    impl/imgui_impl_opengl3.h
    impl/imgui_impl_opengl3.cpp)
target_include_directories(${IMPL_LIB} PUBLIC "impl")
target_link_libraries(${IMPL_LIB} PUBLIC
    ${IMGUI_LIB}
    ${IMPLOT_LIB}
    ${GLFW_LIB}
    ${GLAD_LIB})

# all externals
add_library(${EXTERNAL_LIB} INTERFACE)
target_link_libraries(${EXTERNAL_LIB} INTERFACE
    ${IMPL_LIB}
    ${JSON_LIB})
