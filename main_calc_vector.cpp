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
