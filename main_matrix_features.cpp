/**
 * @file main_matrix_features.cpp
 * @author your name (you@domain.com)
 * @brief 行列の特徴
 * @version 0.1
 * @date 2021-03-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <Eigen/Core>
#include <Eigen/LU> // 行列の基本的分解ほか
#include <Eigen/Eigen> // 固有値
#include <iostream>

using namespace Eigen;

int main(int, char**)
{
    // 行列式と逆行列
    // 行列式や逆行列はCoreヘッダーで提供されていないため
    // LUヘッダーをインクルードする必要がある
    {
        Matrix3d M; // 3x3
        M << 1.0, 0.5, 2.3,
            -4.8, 0.9, -1.6,
            3.2, -0.6, -3.7;
        
        std::cout << "M = \n" << M << std::endl;

        std::cout << "Det(M) = " << M.determinant() << std::endl; // 行列式
        std::cout << "Inv(M) = " << M.inverse() << std::endl;
    }

    // 行列の固有値問題
    // Eigenヘッダが必要
    // 自己随伴行列(実数行列では対称行列)の固有値のソルバのコンストラクタを
    // 呼び出し、固有値と固有ベクトルを計算する.
    // 失敗時のチェックには, info()を使う.
    // 固有値はeigenvalues()関数を使う. 固有値は列ベクトルで要素は昇順
    // 最小固有値はeigenvalues()(0)のように添え字で取り出す
    // 最小固有値に対する固有ベクトルを取り出すには、eigenvectors().col(0)
    {
        Matrix3d M; // 対称行列
        M << 1.0, 0.5, 2.3,
            0.5, 0.9, -1.6,
            2.3, -1.6, 4.8;
        std::cout << "M = \n" << M << std::endl;

        // 自己随伴行列(実数行列の場合は対称行列)の固有値ソルバ
        SelfAdjointEigenSolver<Matrix3d> ES(M);

        if (ES.info() != Success)
            abort(); // 失敗したら終了
        
        // 固有値は列ベクトルの形で得られる
        std::cout << "Eigen values of M = \n" << ES.eigenvalues() << std::endl;

        // 固有ベクトルは行列として得られる
        std::cout << "Eigen vectors of M = \n" << ES.eigenvectors() << std::endl;

        // 最小固有値のみ取り出す
        double min_eigen = ES.eigenvalues()(0);
        std::cout << "Min Eigen value of M = " << min_eigen << std::endl;

        // 最小固有値に対応する固有ベクトルを取り出す
        Vector3d min_eigen_vector = ES.eigenvectors().col(0);
        std::cout << "Min Eigen Vector of M = \n"  << min_eigen_vector << std::endl;
    }

    // SelfAdjointEigenSolverの使い方　その２
    // 一度だけコンストラクタを呼び出し、好きな所で固有値問題を解く
    {
        Matrix3d M;
        M << 1.0, 0.5, 2.3,
            0.5, 0.9, -1.6,
            2.3, -1.6, 4.8;
        std::cout << "M = \n" << M << std::endl;

        SelfAdjointEigenSolver<Matrix3d> ES; // ソルバーのみコンストラクタ

        // Mの固有値と固有ベクトルを計算
        ES.compute(M);

        if (ES.info() != Success)
            abort();
        
        // 固有値は列ベクトルの形で得られる
        std::cout << "Eigen values of M = \n" << ES.eigenvalues() << std::endl;
        // 固有ベクトルは行列として得られる
        std::cout << "Eigen vectors of M = \n" << ES.eigenvectors() << std::endl;
    }


    // 一般固有値問題
    // 対称行列 M,N に対する一般固有値問題
    // Mθ = λNθ
    {
        Matrix3d M, N;
        M << 1.0, 0.5, 2.3,
             0.5, 0.9, -1.6,
             2.3, -1.6, 4.8;
        N << 0.3, -0.3, 1.9,
             -0.3, 1.4, -1.1,
             1.9, -1.1, 1.5;

        std::cout << "M = \n" << M << std::endl;
        std::cout << "N = \n" << N << std::endl;

        // 自己随伴行列(実数行列では対称行列)の一般固有値のソルバー
        GeneralizedSelfAdjointEigenSolver<Matrix3d> GES(M,N);

        if (GES.info() != Success)
            abort();
        
        // 一般固有値は列ベクトルの形で得られる
        std::cout << "Generalized Eigen Values of M and N = \n" << GES.eigenvalues() << std::endl;
        // 一般固有ベクトルは行列の形で得られる
        std::cout << "Generalized Eigen Vectors of M and N = \n" << GES.eigenvectors() << std::endl;
    }
}