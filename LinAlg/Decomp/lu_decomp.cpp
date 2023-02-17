/**
 * @file lu_decomp.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-02-17
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <test_utils.hpp>

/**
 * @brief LU分解
 * @note
 * M = LU
 * 正方行列M(nxn)を下三角行列L(nxn)と上三角行列U(nxn)に分解する.
 *
 * Eigenでは, Mが正則行列に限って, M=P^{-1}LU にも分解できる.
 * その際, P^{-1}は置換行列.
 * また, もうひとつの置換行列Q^{-1}を用いて, M=P^{-1}LUQ^{-1}にも分解できる.
 *
 * @warning 部分ピポット法によるPの計算にはMが正則行列である必要がある.
 * @warning LとUは計算結果上, 一つの行列として出力されるので, 各要素を取り出すこと.
 * @warning Lの取り出し方が特殊.
 *
 */

int main(int, char **)
{
    try
    {
        // 部分ピボットによる M=P^{-1}*L*U への分解
        {
            Eigen::Matrix3d M;
            M << 5.0, 1.0, -2.0,
                1.0, 6.0, -1.0,
                2.0, -1.0, 5.0;

            std::cout << "M = \n"
                      << M << std::endl;

            auto tp_start = high_resolution_clock::now();

            Eigen::PartialPivLU<Eigen::Matrix3d> LUppv(M);

            // 行列L, UとP
            Eigen::Matrix3d P1 = LUppv.permutationP();
            Eigen::Matrix3d U1 = LUppv.matrixLU().triangularView<Eigen::Upper>();         // 行列 U
            Eigen::Matrix3d L1 = LUppv.matrixLU().triangularView<Eigen::StrictlyLower>(); // 行列 L

            L1 += Eigen::Matrix3d::Identity(3, 3); // 単位行列を足して完全な行列 L となる

            auto tp_end = high_resolution_clock::now();
            auto duration = tp_end - tp_start;
            double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
            std::cout << "Elapsed Time of ppv LU " << duration_ms << "[ms]" << std::endl;

            std::cout << "P1 = \n"
                      << P1 << std::endl;
            std::cout << "U1 = \n"
                      << U1 << std::endl;
            std::cout << "L1 = \n"
                      << L1 << std::endl;

            std::cout << "P^{-1}*L*U = \n"
                 << P1.inverse() * L1 * U1 << std::endl;
        }

        std::cout << "----------------------------" << std::endl;

        // 完全ピボットによるM=P^{-1}*L*U*Q^{-1}への分解
        {
            Eigen::Matrix3d M;
            M << 5.0, 1.0, -2.0,
                1.0, 6.0, -1.0,
                2.0, -1.0, 5.0;

            std::cout << "M = \n"
                      << M << std::endl;

            auto tp_start = high_resolution_clock::now();

            Eigen::FullPivLU<Eigen::Matrix3d> LUfpv(M);

            // 行列 P, Q, L, U
            Eigen::Matrix3d P2 = LUfpv.permutationP();
            Eigen::Matrix3d Q2 = LUfpv.permutationQ();
            Eigen::Matrix3d U2 = LUfpv.matrixLU().triangularView<Eigen::Upper>(); // 行列 U
            Eigen::Matrix3d L2 = LUfpv.matrixLU().triangularView<Eigen::StrictlyLower>(); // 行列 L の一部

            L2 += Eigen::Matrix3d::Identity(3, 3); // 単位行列を足して完全な行列 L となる

            auto tp_end = high_resolution_clock::now();
            auto duration = tp_end - tp_start;
            double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
            std::cout << "Elapsed Time of fpv LU " << duration_ms << "[ms]" << std::endl;

            std::cout << "Matrix P2 = \n" << P2 << std::endl;
            std::cout << "Matrix L2 = \n" << L2 << std::endl;
            std::cout << "Matrix U2 = \n" << U2 << std::endl;
            std::cout << "Matrix Q2 = \n" << Q2 << std::endl;

            std::cout << "P^{-1}*L*U*Q^{-1} = \n"
                 << P2.inverse() * L2 * U2 * Q2.inverse() << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
