/**
 * @file matrix.cpp
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
        // 簡単なプログラム
        {
            Eigen::Matrix3d M; // 3x3, double

            M << 1.1, 2.2, 3.3,
                4.4, 5.5, 6.6,
                7.7, 8.8, 9.9;
            std::cout << "M = \n"
                      << M << std::endl;

            std::cout << "M(0,0) = " << M(0, 0) << std::endl; // (0,0)要素
            std::cout << "M(1,2) = " << M(1, 2) << std::endl; // (1,2)要素
            std::cout << "M(2,2) = " << M(2, 2) << std::endl; // (2,2)要素
        }

        // 行列の演算
        {
            Eigen::Matrix3d A, Ac, Am, As, As2, sA, Ad, Ad2, A2, A3, A4, B, C, D, E;
            double s;

            // ランダムな要素の行列を生成
            A = Eigen::Matrix3d::Random();
            B = Eigen::Matrix3d::Random();

            std::cout << "A = \n"
                      << A << std::endl;
            std::cout << "B = \n"
                      << B << std::endl;

            Ac = A;  // 代入(値のコピー)
            Am = -A; // 単項のマイナス

            std::cout << "Ac = \n"
                      << Ac << std::endl;
            std::cout << "Am = \n"
                      << Am << std::endl;

            s = 3.0;
            sA = s * A;    // スカラー倍
            As = A * s;    // スカラー倍
            Ad = A / s;    // スカラー除算
            As2 = Ad2 = A; // 多重代入も可能
            As2 *= s;      // 代入演算子によるスカラー倍
            Ad2 /= s;      // 代入演算子によるスカラー除算

            std::cout << "sA = \n"
                      << sA << std::endl;
            std::cout << "As = \n"
                      << As << std::endl;
            std::cout << "As2 = \n"
                      << As2 << std::endl;
            std::cout << "Ad = \n"
                      << Ad << std::endl;

            A2 = A3 = A4 = A;
            C = A + B; // 行列の加算
            D = A - B;
            E = A * B;
            A2 += B;
            A3 -= B;
            A4 *= B;

            std::cout << "A + B = \n"
                      << C << std::endl;
            std::cout << "A - B = \n"
                      << D << std::endl;
            std::cout << "A * B = \n"
                      << E << std::endl;
            std::cout << "A2 = \n"
                      << A2 << std::endl;
            std::cout << "A3 = \n"
                      << A3 << std::endl;
            std::cout << "A4 = \n"
                      << A4 << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}