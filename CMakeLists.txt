cmake_minimum_required(VERSION 3.0.0)
project(MyEigen VERSION 0.1.0)

# include(CTest)
# enable_testing()

# add_executable(MyEigen main.cpp)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

include_directories(${CMAKE_SOURCE_DIR}/eigen/3.3.4/include/eigen3)


add_executable(calc_vector
    main_calc_vector.cpp
)

add_executable(calc_matrix
    main_calc_matrix.cpp
)