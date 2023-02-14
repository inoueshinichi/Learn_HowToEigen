/**
 * @file vector_initialize.cpp
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
 * @brief ベクトルの初期化
 *
 * @return int
 */

int main(int, char**)
{
    try
    {
        // コンストラクタによる初期化
        Eigen::Vector3d a(0.5, 1.0, -2.4);
        Eigen::Vector3d v1, v2, v3, v4, v5, v6, v7, v8;

        // カンマ演算子とシフト演算子による初期化
        v1 << 1.0, 0.7, -0.52;

        // 要素を直接指定する初期化
        v2(0) = 3.0;
        v2(1) = 1.0;
        v2(2) = -2.0;

        std::cout << "a = " << a.transpose() << std::endl;
        std::cout << "v1 = " << v1.transpose() << std::endl;
        std::cout << "v2 = " << v2.transpose() << std::endl;

        // 単位ベクトル(1,0,0)による初期化
        v1 = Eigen::Vector3d::Identity();

        // ゼロベクトル(0,0,0)による初期化
        v2 = Eigen::Vector3d::Zero();

        // すべての要素が1のベクトルへ初期化
        v3 = Eigen::Vector3d::Ones();

        // X軸方向の単位ベクトルへの初期化
        v4 = Eigen::Vector3d::UnitX();

        // Y軸方向の単位ベクトルへの初期化
        v5 = Eigen::Vector3d::UnitY();

        // Z軸方向の単位ベクトルへの初期化
        v6 = Eigen::Vector3d::UnitZ();

        // ランダムな値での初期化
        v7 = Eigen::Vector3d::Random();

        // すべて同じ値による初期化
        v8 = Eigen::Vector3d::Constant(0.1);

        // データ順序を列優先から行優先に変更(転置)して表示
        std::cout << "v1 = " << v1.transpose() << std::endl;
        std::cout << "v2 = " << v2.transpose() << std::endl;
        std::cout << "v3 = " << v3.transpose() << std::endl;
        std::cout << "v4 = " << v4.transpose() << std::endl;
        std::cout << "v5 = " << v5.transpose() << std::endl;
        std::cout << "v6 = " << v6.transpose() << std::endl;
        std::cout << "v7 = " << v7.transpose() << std::endl;
        std::cout << "v8 = " << v8.transpose() << std::endl;

        std::cout << "-------------------------" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    return 0;
}