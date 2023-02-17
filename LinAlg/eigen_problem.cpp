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

/**
 * @brief 固有値問題
 * @note
 * Mx=λx (Mは対称行列, λは固有値, x!=0)から固有値と固有ベクトルを求める方法
 * 自己随伴行列(実数行列では対称行列)の固有値のソルバのコンストラクタを呼び出して
 * 固有値と固有ベクトルを計算する.失敗時のチェックにはinfo()を使用する.
 * 固有値はeigenvalues()関数を使う. 固有値は列ベクトルで要素は昇順に格納される.
 * 最小固有値はeigenvalues()(0)のように添え字で取り出す.
 * 最小固有値に対する固有ベクトルを取り出すには、eigenvectors().col(0)
 * 
 * #include <Eigen/Eigen>が必要.
 *
 * @return int
 */

int main(int, char **)
{
    try
    {
        Eigen::Matrix3d M; // 対称行列
        M << 1.0, 0.5, 2.3,
            0.5, 0.9, -1.6,
            2.3, -1.6, 4.8;
        std::cout << "M = \n"
                  << M << std::endl;

        // 自己随伴行列の固有値ソルバ
        Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> SAES;

        auto tp_start = high_resolution_clock::now();

        SAES.compute(M); // 固有値と固有ベクトルを計算

        auto tp_end = high_resolution_clock::now();
        auto duration = tp_end - tp_start;
        double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
        std::cout << "Elapsed Time of EigenSolver " << duration_ms << "[ms]" << std::endl;

        if (SAES.info() != Eigen::Success)
            std::abort(); // 失敗したら終了

        // 固有値は列ベクトルの形で得られる
        std::cout << "Eigen values of M = \n"
                  << SAES.eigenvalues() << std::endl;

        // 固有ベクトルは行列として得られる(列ベクトルが各固有ベクトルであり, 固有値に対応)
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
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}