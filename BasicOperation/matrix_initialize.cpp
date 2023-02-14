/**
 * @file matrix_initialize.cpp
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
        // 行列の初期化
        Eigen::Matrix3d M1, M2, M3, M4, M5, M6, M7;

        // コンストラクタによる初期化はエラー
        // Matrix3d M(0.5, 1.0, -2.4, 0.0, 1.1, 0.2, -0.6, 2.1, 3.4);

        // カンマ演算子とシフト演算子による初期化
        M1 << 1.0, 0.7, -0.52, 0.0, 2.0, -1.4, 3.9, -5.2, 1.22;

        // 要素を直接指定して代入
        M2(0, 0) = 1.23;
        M2(0, 1) = 2.34;
        M2(0, 2) = 3.45;
        M2(1, 0) = 4.56;
        M2(1, 1) = 5.67;
        M2(1, 2) = 6.78;
        M2(2, 0) = 7.89;
        M2(2, 1) = 8.91;
        M2(2, 2) = 9.12;

        M3 = Eigen::Matrix3d::Identity();    // 単位行列
        M4 = Eigen::Matrix3d::Zero();        // ゼロ行列
        M5 = Eigen::Matrix3d::Ones();        // すべての要素が1の行列
        M6 = Eigen::Matrix3d::Random();      // ランダムな値の行列
        M7 = Eigen::Matrix3d::Constant(0.1); // すべての要素が同じの行列

        std::cout << "M1 = \n"
                  << M1 << std::endl;
        std::cout << "M2 = \n"
                  << M2 << std::endl;
        std::cout << "M3 = \n"
                  << M3 << std::endl;
        std::cout << "M4 = \n"
                  << M4 << std::endl;
        std::cout << "M5 = \n"
                  << M5 << std::endl;
        std::cout << "M6 = \n"
                  << M6 << std::endl;
        std::cout << "M7 = \n"
                  << M7 << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}