# Sources and Headers
set(ADAS_LIB_SOURCES
    "AdFunctions.cc")

# Library
add_library(${ADAS_LIB} ${ADAS_LIB_SOURCES})
target_include_directories(${ADAS_LIB} PUBLIC "./")
target_link_libraries(${ADAS_LIB} PUBLIC
    ${UTIL_LIB})
target_set_warnings(TARGET ${ADAS_LIB} ENABLE ON AS_ERROR OFF)
