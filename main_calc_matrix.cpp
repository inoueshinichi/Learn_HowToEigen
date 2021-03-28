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

        std::cout << "M(0,0) = " << M(0,0) << std::endl; // (0,0)要素
        std::cout << "M(1,2) = " << M(1,2) << std::endl; // (1,2)要素
        std::cout << "M(2,2) = " << M(2,2) << std::endl; // (2,2)要素
    }

    // 行列の初期化
    {
        Matrix3d M1, M2, M3, M4, M5, M6, M7;

        // コンストラクタによる初期化はエラー
        // Matrix3d M(0.5, 1.0, -2.4, 0.0, 1.1, 0.2, -0.6, 2.1, 3.4);

        // カンマ演算子とシフト演算子による初期化
        M1 << 1.0, 0.7, -0.52, 0.0, 2.0, -1.4, 3.9, -5.2, 1.22;

        // 要素を直接指定して代入
        M2(0,0) = 1.23; M2(0,1) = 2.34; M2(0,2) = 3.45;
        M2(1,0) = 4.56; M2(1,1) = 5.67; M2(1,2) = 6.78;
        M2(2,0) = 7.89; M2(2,1) = 8.91; M2(2,2) = 9.12;

        M3 = Matrix3d::Identity(); // 単位行列
        M4 = Matrix3d::Zero(); // ゼロ行列
        M5 = Matrix3d::Ones(); // すべての要素が1の行列
        M6 = Matrix3d::Random(); // ランダムな値の行列
        M7 = Matrix3d::Constant(0.1); // すべての要素が同じの行列

        std::cout << "M1 = \n" << M1 << std::endl;
        std::cout << "M2 = \n" << M2 << std::endl;
        std::cout << "M3 = \n" << M3 << std::endl;
        std::cout << "M4 = \n" << M4 << std::endl;
        std::cout << "M5 = \n" << M5 << std::endl;
        std::cout << "M6 = \n" << M6 << std::endl;
        std::cout << "M7 = \n" << M7 << std::endl;
    }

    // 行列の次元と型
    // Matrix[次元][型]
    // 次元：2,3,4,X
    // 型：d,f,i
    {
        // よく使われる2x2, 3x3, 4x4行列は用意されている
        Matrix2d A; // double 2x2
        Matrix2f B; // float 2x2
        Matrix2i C; // int 2x2

        Matrix3d D;
        Matrix3f E;
        Matrix3i F;

        Matrix4d G;
        Matrix4f H;
        Matrix4i P;

        MatrixXd Q;
        MatrixXf R;
        MatrixXi S;
    }

    // 行列の演算
    {
        Matrix3d A, Ac, Am, As, As2, sA, Ad, Ad2, A2, A3, A4, B, C, D, E;
        double s;

        // ランダムな要素の行列を生成
        A = Matrix3d::Random();
        B = Matrix3d::Random();

        std::cout << "A = \n" << A << std::endl;
        std::cout << "B = \n" << B << std::endl;

        Ac = A; // 代入(値のコピー)
        Am = -A; // 単項のマイナス

        std::cout << "Ac = \n" << Ac << std::endl;
        std::cout << "Am = \n" << Am << std::endl;

        s = 3.0;
        sA = s * A; // スカラー倍
        As = A * s; // スカラー倍
        Ad = A / s; // スカラー除算
        As2 = Ad2 = A; // 多重代入も可能
        As2 *= s; // 代入演算子によるスカラー倍
        Ad2 /= s; // 代入演算子によるスカラー除算

        std::cout << "sA = \n" << sA << std::endl;
        std::cout << "As = \n" << As << std::endl;
        std::cout << "As2 = \n" << As2 << std::endl;
        std::cout << "Ad = \n" << Ad << std::endl;

        A2 = A3 = A4 = A;
        C = A + B; //行列の加算
        D = A - B;
        E = A * B;
        A2 += B;
        A3 -= B;
        A4 *= B;

        std::cout << "A + B = \n" << C << std::endl;
        std::cout << "A - B = \n" << D << std::endl;
        std::cout << "A * B = \n" << E << std::endl;
        std::cout << "A2 = \n" << A2 << std::endl;
        std::cout << "A3 = \n" << A3 << std::endl;
        std::cout << "A4 = \n" << A4 << std::endl;
    }

    // 他のサイズの行列や特殊な行列
    {
        // 対角行列
        using DiagMatrix3d = DiagonalMatrix<double, 3>;

        DiagMatrix3d D1, D2;
        DiagonalMatrix<double, 3> D3(1.23, 2.34, 3.45); // コンストラクタによる初期化

        // std::cout << "DiagMatrix3d = \n" << D1 << std::endl;

        Vector3d v1, v2;
        v1 = Vector3d::Random();
        D1.diagonal() = v1; // ベクトルによる初期化

        v2 = Vector3d::Ones();
        D2 = v2.asDiagonal(); // ベクトルを対角行列に変換する初期化

        std::cout << "D1 = \n" << D1.diagonal() << std::endl;
        std::cout << "D2 = \n" << D2.diagonal() << std::endl;
        std::cout << "D3 = \n" << D3.diagonal() << std::endl;

        Matrix3d M, M1, M2;
        M = Matrix3d::Random();
        M1 = D1; // 通常の行列への代入
        M2 = D1 * M; // 通常の行列との積

        std::cout << "M1 = \n" << M1 << std::endl;
        std::cout << "M2 = \n" << M2 << std::endl;
    }
}