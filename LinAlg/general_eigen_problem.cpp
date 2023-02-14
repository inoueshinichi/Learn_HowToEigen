/**
 * @file general_eigen_problem.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <test_utils.hpp>

int main(int, char **)
{
    try
    {
        // 一般固有値問題
        // 対称行列 M,N に対する一般固有値問題
        // Mθ = λNθ
        {
            Eigen::Matrix3d M, N;
            M << 1.0, 0.5, 2.3,
                0.5, 0.9, -1.6,
                2.3, -1.6, 4.8;
            N << 0.3, -0.3, 1.9,
                -0.3, 1.4, -1.1,
                1.9, -1.1, 1.5;

            std::cout << "M = \n"
                      << M << std::endl;
            std::cout << "N = \n"
                      << N << std::endl;

            // 自己随伴行列(実数行列では対称行列)の一般固有値のソルバー
            Eigen::GeneralizedSelfAdjointEigenSolver<Eigen::Matrix3d> GES;

            GES.compute(M,N);

            if (GES.info() != Eigen::Success)
                abort();

            // 一般固有値は列ベクトルの形で得られる
            std::cout << "Generalized Eigen Values of M and N = \n"
                      << GES.eigenvalues() << std::endl;
            // 一般固有ベクトルは行列の形で得られる
            std::cout << "Generalized Eigen Vectors of M and N = \n"
                      << GES.eigenvectors() << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}