add_executable(${EXE_NAME}
        Cycle.cc
        Main.cc)
target_set_warnings(TARGET ${EXE_NAME} ENABLE ON AS_ERROR OFF)

target_link_libraries(${EXE_NAME} PUBLIC
    ${EXTERNAL_LIB}
    ${ALGO_LIB})
