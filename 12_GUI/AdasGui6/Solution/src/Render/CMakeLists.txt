# Sources and Headers
set(RENDER_LIB_SOURCES
    "Render.cc")

# Library
add_library(${RENDER_LIB} ${RENDER_LIB_SOURCES})
target_include_directories(${RENDER_LIB} PUBLIC "./")
target_link_libraries(${RENDER_LIB} PUBLIC
    ${EXTERNAL_LIB}
    ${DATA_LOADER_LIB}
    ${UTIL_LIB})
target_set_warnings(TARGET ${RENDER_LIB} ENABLE ON AS_ERROR OFF)
