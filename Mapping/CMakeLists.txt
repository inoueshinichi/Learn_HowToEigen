cmake_minimum_required(VERSION 3.14.6)

include(../eigen_test_case.cmake)

make_test_case_eigen(EIGEN_MA_MAP_VECTOR ./map_vector.cpp)
make_test_case_eigen(EIGEN_MA_MAP_MATRIX ./map_matrix.cpp)
