/**
 * @file general_eigen_problem.cpp
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
 * @brief 一般固有値問題
 * @note
 * Mx=λNx (M,Nは対称行列, λは固有値, x!=0)から固有値と固有ベクトルを取得する.
 * GeneralizedSelfAdjointEigenSolverクラスを使用する以外は固有値問題と同じ
 * プログラムで大丈夫.
 * 
 * #include <Eigen/Eigen>が必要.
 *
 * @return int
 */

int main(int, char **)
{
    try
    {
        // 一般固有値問題
        // 対称行列 M,N に対する一般固有値問題
        // Mθ = λNθ
        {
            Eigen::Matrix3d M, N;
            M << 1.0, 0.5, 2.3,
                0.5, 0.9, -1.6,
                2.3, -1.6, 4.8;
            N << 0.3, -0.3, 1.9,
                -0.3, 1.4, -1.1,
                1.9, -1.1, 1.5;

            std::cout << "M = \n"
                      << M << std::endl;
            std::cout << "N = \n"
                      << N << std::endl;

            // 自己随伴行列(実数行列では対称行列)の一般固有値のソルバー
            Eigen::GeneralizedSelfAdjointEigenSolver<Eigen::Matrix3d> GES;

            auto tp_start = high_resolution_clock::now();

            GES.compute(M,N); // 固有値と固有ベクトルを計算

            auto tp_end = high_resolution_clock::now();
            auto duration = tp_end - tp_start;
            double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
            std::cout << "Elapsed Time of Gen EigenSolver " << duration_ms << "[ms]" << std::endl;

            if (GES.info() != Eigen::Success)
                abort();

            // 一般固有値は列ベクトルの形で得られる(昇順で格納. 0, 1, 2, ... , Max)
            std::cout << "Generalized Eigen Values of M and N = \n"
                      << GES.eigenvalues() << std::endl;
            // 一般固有ベクトルは行列の形で得られる(列ベクトルが固有値に対応する固有ベクトル)
            std::cout << "Generalized Eigen Vectors of M and N = \n"
                      << GES.eigenvectors() << std::endl;

            // 最小固有値
            std::cout << "Min Eigen Value of M and N = \n"
                << GES.eigenvalues()(0) << std::endl;
            // 最小固有値に対応する固有ベクトル
            std::cout << "Min Eigen Vector of M and N = \n"
                << GES.eigenvectors().col(0) << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}