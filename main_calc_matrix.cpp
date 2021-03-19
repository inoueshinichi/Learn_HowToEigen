/**
 * @file main_calc_matrix.cpp
 * @author your name (you@domain.com)
 * @brief 行列のその演算
 * @version 0.1
 * @date 2021-03-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <Eigen/Core>
#include <iostream>

using namespace Eigen;

int main(int,char**)
{
    // 簡単なプログラム
    {
        Matrix3d M; // 3x3, double

        M << 1.1, 2.2, 3.3,
             4.4, 5.5, 6.6,
             7.7, 8.8, 9.9;
        std::cout << "M = \n" << M << std::endl;
    }
}