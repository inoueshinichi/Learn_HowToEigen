cmake_minimum_required(VERSION 3.14.6)


function(make_test_case_eigen TEST_TARGET TERGET_SOURCES)

    # Project
    project(${TEST_TARGET} LANGUAGES CXX VERSION 0.1.0)

    # Header
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})

    # Executable
    add_executable(${TEST_TARGET} ${TERGET_SOURCES})

    # Eigen
    include_directories(${TEST_TARGET} ${CMAKE_SOURCE_DIR}/eigen/3.3.4/include/eigen3)

endfunction()