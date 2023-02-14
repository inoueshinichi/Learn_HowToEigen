/**
 * @file eigen_problem.cpp
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
        // 行列の固有値問題
        // Eigenヘッダが必要
        // 自己随伴行列(実数行列では対称行列)の固有値のソルバのコンストラクタを
        // 呼び出し、固有値と固有ベクトルを計算する.
        // 失敗時のチェックには, info()を使う.
        // 固有値はeigenvalues()関数を使う. 固有値は列ベクトルで要素は昇順
        // 最小固有値はeigenvalues()(0)のように添え字で取り出す
        // 最小固有値に対する固有ベクトルを取り出すには、eigenvectors().col(0)
        {
            Eigen::Matrix3d M; // 対称行列
            M << 1.0, 0.5, 2.3,
                0.5, 0.9, -1.6,
                2.3, -1.6, 4.8;
            std::cout << "M = \n"
                      << M << std::endl;

            // 自己随伴行列(実数行列の場合は対称行列)の固有値ソルバ
            // Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> SAES(M);
            Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> SAES;

            SAES.compute(M);

            if (SAES.info() != Eigen::Success)
                std::abort(); // 失敗したら終了

            // 固有値は列ベクトルの形で得られる
            std::cout << "Eigen values of M = \n"
                      << SAES.eigenvalues() << std::endl;

            // 固有ベクトルは行列として得られる
            std::cout << "Eigen vectors of M = \n"
                      << SAES.eigenvectors() << std::endl;

            // 最小固有値のみ取り出す
            double min_eigen = SAES.eigenvalues()(0);
            std::cout << "Min Eigen value of M = " << min_eigen << std::endl;

            // 最小固有値に対応する固有ベクトルを取り出す
            Eigen::Vector3d min_eigen_vector = SAES.eigenvectors().col(0);
            std::cout << "Min Eigen Vector of M = \n"
                      << min_eigen_vector << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}