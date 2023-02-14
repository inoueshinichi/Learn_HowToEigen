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
        {
            Eigen::Vector3d a; // 3次元ベクトル, 要素はdouble

            a << 1.0, 0.7, -0.52;
            std::cout << "a = " << a << std::endl;
            std::cout << "a.T = " << a.transpose() << std::endl; // 転値
            std::cout << "a(0) = " << a(0) << std::endl;         // 0
            std::cout << "a(1) = " << a(1) << std::endl;         // 1
            std::cout << "a(2) = " << a(2) << std::endl;         // 2
            std::cout << "-------------------------" << std::endl;
        }

        // ベクトルの基本演算
        {
            Eigen::Vector3d a, ac, am, sa, as, ad, as2, ad2, a2, a3, b, c, d, vp, n;
            double ip, s, nrm, sqnrm;

            a = Eigen::Vector3d::Random();
            b = Eigen::Vector3d::Random();
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
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}