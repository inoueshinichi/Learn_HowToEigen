/**
 * @file diag_matrix.cpp
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
        // 他のサイズの行列や特殊な行列
        {
            // 対角行列
            using DiagMatrix3d = Eigen::DiagonalMatrix<double, 3>;

            DiagMatrix3d D1, D2;
            Eigen::DiagonalMatrix<double, 3> D3(1.23, 2.34, 3.45); // コンストラクタによる初期化

            // std::cout << "DiagMatrix3d = " << D1 << std::endl; // DiagonalMatrixは<< operatorを持たない
            Eigen::Matrix3d tmpD1 = D1;
            std::cout << "DiagMatrix3d = " << tmpD1 << std::endl;

            Eigen::Vector3d v1, v2;
            v1 = Eigen::Vector3d::Random();
            D1.diagonal() = v1; // ベクトルによる初期化

            v2 = Eigen::Vector3d::Ones();
            D2 = v2.asDiagonal(); // ベクトルを対角行列に変換する初期化

            std::cout << "D1 = \n"
                      << D1.diagonal() << std::endl;
            std::cout << "D2 = \n"
                      << D2.diagonal() << std::endl;
            std::cout << "D3 = \n"
                      << D3.diagonal() << std::endl;

            Eigen::Matrix3d M, M1, M2;
            M = Eigen::Matrix3d::Random();
            M1 = D1;     // 通常の行列への代入
            M2 = D1 * M; // 通常の行列との積

            std::cout << "M1 = \n"
                      << M1 << std::endl;
            std::cout << "M2 = \n"
                      << M2 << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}