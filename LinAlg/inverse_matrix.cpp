/**
 * @file inverse_matrix.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <test_utils.hpp>

/**
 * @brief 逆行列
 * @note
 * LU分解を用いて計算する.
 * 
 * #include <Eigen/LU>が必要.
 * 
 * @return int 
 */

int main(int, char **)
{
    try
    {
        // 行列式と逆行列
        {
            Eigen::Matrix3d M; // 3x3
            M << 1.0, 0.5, 2.3,
                -4.8, 0.9, -1.6,
                3.2, -0.6, -3.7;

            std::cout << "M = \n"
                      << M << std::endl;

            std::cout << "Det(M) = " << M.determinant() << std::endl; // 行列式
            std::cout << "Inv(M) = " << M.inverse() << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}