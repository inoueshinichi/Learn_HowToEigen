cmake_minimum_required(VERSION 3.14.6)

include(../eigen_test_case.cmake)

make_test_case_eigen(EIGEN_LINALG_EIGEN_PROBLEM ./eigen_problem.cpp)
make_test_case_eigen(EIGEN_LINALG_GENERAL_EIGEN_PROBLEM ./general_eigen_problem.cpp)