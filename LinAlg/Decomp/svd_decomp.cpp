/**
 * @file svd_decomp.cpp
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
        // 正方行列の特異値分解
        // M = UΣV^T
        // 行列UとVは直行行列
        // 行列Σは対角行列. その対角要素が特異値.
        // 特異値は、降順にソートされた列ベクトルとして出力される
        {
            Matrix3d M;
            M << 1.0, 0.5, 2.3,
                0.5, 0.9, -1.6,
                2.3, -1.6, 4.8;
            std::cout << "M = \n"
                      << M << std::endl;

            // 特異値分解
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}