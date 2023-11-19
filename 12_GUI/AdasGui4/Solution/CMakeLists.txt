cmake_minimum_required(VERSION 3.17)

set(PROJECT "AdasGui")
project(${PROJECT} VERSION 0.1.0 LANGUAGES C CXX)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD              17)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)

# Options
option(ENABLE_WARNINGS  "Enable to add warnings to a target." ON)

# Cmake modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
include(ConfigSafeGuards)
if (ENABLE_WARNINGS)
    include(Warnings)
endif()

# Project/Library Names
set(IMGUI_LIB     imgui)
set(GLFW_LIB      glfw)
set(GLAD_LIB      glad)
set(IMPL_LIB      impl)
set(IMPLOT_LIB    implot)
set(JSON_LIB      json)
add_subdirectory(external)

set(ADAS_LIB      lib)
set(EXE_NAME      AdasGui)
add_subdirectory(src)

add_executable(${EXE_NAME}
        app/cycle.cpp
        app/main.cpp)
target_set_warnings(TARGET ${EXE_NAME} ENABLE ON AS_ERROR OFF)

target_link_libraries(${EXE_NAME} PUBLIC
    ${IMPL_LIB}
    ${IMGUI_LIB}
    ${IMPLOT_LIB}
    ${ADAS_LIB})
