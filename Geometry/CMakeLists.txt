cmake_minimum_required(VERSION 3.14.6)

include(../eigen_test_case.cmake)

make_test_case_eigen(EIGEN_GEOMETRY_TRANSFORMER ./geometry_3d_transformer.cpp)