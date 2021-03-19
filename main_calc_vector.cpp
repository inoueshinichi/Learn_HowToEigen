/**
 * @file main_calc_vector.cpp
 * @author your name (you@domain.com)
 * @brief ベクトルとその演算
 * @version 0.1
 * @date 2021-03-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>

#include <Eigen/Core> // 基本演算
#include <Eigen/Geometry> // cross

using namespace Eigen;

int main(int, char**) 
{
    // ベクトルの簡単なプログラム
    {
        Vector3d a; // 3次元ベクトル, 要素はdouble

        a << 1.0, 0.7, -0.52;
        std::cout << "a = " << a << std::endl;
        std::cout << "a.T = " << a.transpose() << std::endl; // 転値
        std::cout << "a(0) = " << a(0) << std::endl; // 0
        std::cout << "a(1) = " << a(1) << std::endl; // 1
        std::cout << "a(2) = " << a(2) << std::endl; // 2
        std::cout << "-------------------------" << std::endl;
    }

    // ベクトルの初期化
    {
        // コンストラクタによる初期化
        Vector3d a(0.5, 1.0, -2.4);
        Vector3d v1, v2, v3, v4, v5, v6, v7, v8;

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
        v1 = Vector3d::Identity();
        
        // ゼロベクトル(0,0,0)による初期化
        v2 = Vector3d::Zero();

        // すべての要素が1のベクトルへ初期化
        v3 = Vector3d::Ones();

        // X軸方向の単位ベクトルへの初期化
        v4 = Vector3d::UnitX();

        // Y軸方向の単位ベクトルへの初期化
        v5 = Vector3d::UnitY();
        
        // Z軸方向の単位ベクトルへの初期化
        v6 = Vector3d::UnitZ();

        // ランダムな値での初期化
        v7 = Vector3d::Random();

        // すべて同じ値による初期化
        v8 = Vector3d::Constant(0.1);

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

    // ベクトルの次元と型
    {
        // Vector[次元][型]
        // 次元：2,3,4,X(動的)
        // 型: d,f,i

        // よく使われる2次元、3次元、4次元ベクトルは用意されている
        Vector2d a; // double
        Vector2f b; // float
        Vector2i c; // int
        Vector3d d;
        Vector3f e;
        Vector3i f;
        Vector4d g;
        Vector4f h;
        Vector4i i;
        // 複素数型も用意されている

        // 可変長次元ベクトル
        VectorXd p;
        VectorXf q;
        VectorXi r;

        // usingを使ってエイリアスにする
        using Vector6d = Matrix<double, 6, 1>;
        using Vector9d = Matrix<double, 9, 1>;
        using Vector6i = Matrix<int, 6, 1>;
        using Vector9f = Matrix<float, 9, 1>;

        // Eigenでは、コンパイル時にサイズ(=次元)が決まっているものを「固定サイズ」,
        // コンパイル時にサイズが分からないものを「動的サイズ」と呼ぶ。
        // 16次元以下であれば、固定サイズのほうが効率が良い。
    }

    // ベクトルの基本演算
    {
        Vector3d a, ac, am, sa, as, ad, as2, ad2, a2, a3, b, c, d, vp, n;
        double ip, s, nrm, sqnrm;

        a = Vector3d::Random();
        b = Vector3d::Random();
        std::cout << "a = " << a.transpose() << std::endl;
        std::cout << "b = " << b.transpose() << std::endl;

        // ベクトルの代入(コピー)
        ac = a;

        // 単項の−
        am = -a;

        std::cout << "ac = " << ac.transpose() << std::endl;
        std::cout << "am = " << am.transpose() << std::endl;

        // 多重代入
        s = 3.0;
        as2 = ad2 = a;

        // ベクトルのスカラー倍
        sa = s * a;
        as = a * s;
        ad = a / s;
        as2 *= s;
        ad2 /= s;
        std::cout << "sa = " << sa.transpose() << std::endl;
        std::cout << "as = " << as.transpose() << std::endl;
        std::cout << "ad = " << ad.transpose() << std::endl;
        std::cout << "as2 = " << as2.transpose() << std::endl;
        std::cout << "ad2 = " << ad2.transpose() << std::endl;

        // ベクトルの和及び差
        a2 = a3 = a;
        c = a + b;
        d = a - b;
        a2 += b;
        a3 -= b;

        std::cout << "a2 = " << a2.transpose() << std::endl;
        std::cout << "c = " << c.transpose() << std::endl;
        std::cout << "d = " << d.transpose() << std::endl;
        std::cout << "a2 = " << a2.transpose() << std::endl;
        std::cout << "a3 = " << a3.transpose() << std::endl;

        // ベクトルの内積
        ip = a.dot(b);

        // ベクトル積 ※幾何学演算の1つであるため、Geometoryヘッダーが必要
        vp = a.cross(b); // 外積

        std::cout << "dot(a,b) = " << ip << std::endl;
        std::cout << "cross(a,b) = " << vp.transpose() << std::endl;

        // ベクトルのノルム
        n = a;
        nrm = a.norm();

        // 単位ベクトルへ直接正規化する関数
        n.normalize();

        // 2乗ノルム
        sqnrm = a.squaredNorm();

        std::cout << "norm of a = " << nrm << std::endl;
        std::cout << "normalized a = " << n << std::endl;
        std::cout << "squred norm of a = " << sqnrm << std::endl;

        std::cout << "-------------------------" << std::endl;

    }
}
