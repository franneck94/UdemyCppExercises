set(UTIL_LIB        UtilLib)
set(ADAS_LIB        AdLib)
set(PERCEPTION_LIB  PerceptionLib)
set(DATA_LOADER_LIB DataLoaderLib)
set(RENDER_LIB      RenderLib)

add_subdirectory(Util)
add_subdirectory(DataLoader)
add_subdirectory(Perception)
add_subdirectory(AutomatedDriving)
add_subdirectory(Render)

# all internals
add_library(${ALGO_LIB} INTERFACE)
target_link_libraries(${ALGO_LIB} INTERFACE
    ${EXTERNAL_LIB}
    ${UTIL_LIB}
    ${ADAS_LIB}
    ${DATA_LOADER_LIB}
    ${RENDER_LIB})
