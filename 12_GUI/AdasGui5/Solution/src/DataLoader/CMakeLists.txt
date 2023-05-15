# Sources and Headers
set(DATA_LOADER_LIB_SOURCES
    "DataLoader.cc")

# Library
add_library(${DATA_LOADER_LIB} ${DATA_LOADER_LIB_SOURCES})
target_include_directories(${DATA_LOADER_LIB} PUBLIC "./")
target_link_libraries(${DATA_LOADER_LIB} PUBLIC
    ${EXTERNAL_LIB}
    ${ADAS_LIB}
    ${UTIL_LIB})
target_set_warnings(TARGET ${DATA_LOADER_LIB} ENABLE ON AS_ERROR OFF)
