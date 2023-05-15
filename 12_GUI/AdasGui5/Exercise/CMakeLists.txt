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
set(EXTERNAL_LIB    ExternalLib)
add_subdirectory(external)

set(ALGO_LIB        AdasAlgo)
add_subdirectory(src)

set(EXE_NAME        AdasGui)
add_subdirectory(app)
