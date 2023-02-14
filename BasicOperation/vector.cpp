/**
 * @file vector.cpp
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
        // ベクトルの簡単なプログラム
        Eigen::Vector3d a; // 3次元ベクトル, 要素はdouble

        a << 1.0, 0.7, -0.52;
        std::cout << "a = " << a << std::endl;
        std::cout << "a.T = " << a.transpose() << std::endl; // 転値
        std::cout << "a(0) = " << a(0) << std::endl;         // 0
        std::cout << "a(1) = " << a(1) << std::endl;         // 1
        std::cout << "a(2) = " << a(2) << std::endl;         // 2
        std::cout << "-------------------------" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}