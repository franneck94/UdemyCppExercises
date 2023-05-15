# Sources and Headers
set(PERCEPTION_LIB_SOURCES
    "Perception.cc")

# Library
add_library(${PERCEPTION_LIB} ${PERCEPTION_LIB_SOURCES})
target_include_directories(${PERCEPTION_LIB} PUBLIC "./")
target_link_libraries(${PERCEPTION_LIB} PUBLIC
    ${EXTERNAL_LIB}
    ${ADAS_LIB}
    ${DATA_LOADER_LIB}
    ${UTIL_LIB})
target_set_warnings(TARGET ${PERCEPTION_LIB} ENABLE ON AS_ERROR OFF)
