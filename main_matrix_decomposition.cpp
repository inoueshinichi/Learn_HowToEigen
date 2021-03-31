/**
 * @file main_matrix_decomposition.cpp
 * @author your name (you@domain.com)
 * @brief 行列の分解
 * @version 0.1
 * @date 2021-03-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <Eigen/Core> // 基本演算のみ
#include <Eigen/SVD>  // 特異値分解

using namespace Eigen;

int main(int, char**)
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
        std::cout << "M = \n" << M << std::endl;

        // 特異値分解
        
    }
}