cmake_minimum_required(VERSION 3.14.6)

include(../eigen_test_case.cmake)

make_test_case_eigen(EIGEN_BO_VECTOR ./vector.cpp)
make_test_case_eigen(EIGEN_BO_VECTOR_INITIALIZE ./vector_initialize.cpp)
make_test_case_eigen(EIGEN_BO_NDIM_TYPE ./ndim_type.cpp)