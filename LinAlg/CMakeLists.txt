cmake_minimum_required(VERSION 3.14.6)

include(../eigen_test_case.cmake)

# Easy inverse (still 4x4)
make_test_case_eigen(EIGEN_LINALG_INVERSE_MATRIX ./inverse_matrix.cpp)

# Eigen problem
make_test_case_eigen(EIGEN_LINALG_EIGEN_PROBLEM ./eigen_problem.cpp)
make_test_case_eigen(EIGEN_LINALG_GENERAL_EIGEN_PROBLEM ./general_eigen_problem.cpp)

# Decomp directory
make_test_case_eigen(EIGEN_LINALG_DECOMP_SVD ./Decomp/svd_decomp.cpp)
make_test_case_eigen(EIGEN_LINALG_DECOMP_LU ./Decomp/lu_decomp.cpp)
make_test_case_eigen(EIGEN_LINALG_DECOMP_CHOLESKY ./Decomp/cholesky_decomp.cpp)
make_test_case_eigen(EIGEN_LINALG_DECOMP_QR ./Decomp/qr_decomp.cpp)

# Inverse
make_test_case_eigen(EIGEN_LINALG_GENERAL_INVERSE_MATRIX ./general_inverse_matrix.cpp)

# Solver
make_test_case_eigen(EIGEN_LINALG_LINALG_SOLVER ./linalg_solver.cpp)

# Relative Error
make_test_case_eigen(EIGEN_LINALG_RELATIVE_ERROR ./linalg_relative_error.cpp)

make_test_case_eigen(EIGEN_LINALG_LEAST_SQUARE ./linalg_least_square.cpp)