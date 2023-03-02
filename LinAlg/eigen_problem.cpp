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
 * @brief 固有値問題 : Mx=λx (x != 0)の非自明解となる固有値λを求める
 * 行列M(mxn)について
 * 1. 実対称行列 or 自己自己随伴行列 (自動的に正方&正則) : フルランク -> SelfAdjointEigenSolver
 * 2. 実行列(非正方でOK) : 優決定系,劣決定系,ランク落ち -> EigenSolver
 * 3. 複素行列(非正方でOK) : 優決定系,劣決定系,ランク落ち -> ComplexEigenSolver
 *
 * @return int
 */

template <typename MAT>
void CheckRank(const MAT &mat)
{
#define STR(name) #name
    std::cout << "Mat size (" << mat.rows() << "," << mat.cols() << ")" << std::endl;
    std::cout << "[Check] Matrix rank" << std::endl;
    Eigen::FullPivLU<MAT> FPLU(mat);
    std::cout << "Rank of " << STR(MAT) << ": " << FPLU.rank() << std::endl;
    std::cout << "IsInvertable? -> " << std::boolalpha << FPLU.isInvertible();
    std::cout << std::noboolalpha << std::endl;
#undef STR
}

int main(int, char **)
{
    try
    {
        // 1. 実対称行列 or 自己自己随伴行列 (自動的に正方&正則) : フルランク -> SelfAdjointEigenSolver
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
            std::cout << "Elapsed Time of SelfAdjointEigenSolver " << duration_ms << "[ms]" << std::endl;

            if (SAES.info() != Eigen::Success)
                std::abort(); // 失敗したら終了

            // 固有値は列ベクトルの形で得られる
            std::cout << "Eigen values of [λ1,λ2,...] = \n"
                      << SAES.eigenvalues() << std::endl;

            // 固有ベクトルは行列として得られる(列ベクトルが各固有ベクトルであり, 固有値に対応)
            std::cout << "Eigen vectors of M = \n"
                      << SAES.eigenvectors() << std::endl;

            // 最小固有値のみ取り出す (SelfAdjointEigenSolverとComplexEigenSolverは昇順っぽい. EigenSolverは降順)
            double min_eigen = SAES.eigenvalues()(0);
            std::cout << "Min Eigen value of [v1,v2,...] = " << min_eigen << std::endl;

            // 最小固有値に対応する固有ベクトルを取り出す
            Eigen::Vector3d min_eigen_vector = SAES.eigenvectors().col(0);
            std::cout << "Min Eigen Vector of M = \n"
                      << min_eigen_vector << std::endl;
        }

        std::cout << "------------------" << std::endl;

        // 2. 実行列(非正方でOK) : 優決定系,劣決定系,ランク落ち -> EigenSolver
        {
            Eigen::Matrix3d M;
            M << 1, 2, 2, 0, 1, 1, 0, 0, 0;
            std::cout << "M = \n" << M << std::endl;
            CheckRank(M);

            Eigen::EigenSolver<Eigen::Matrix3d> EVD;

            auto tp_start = high_resolution_clock::now();

            EVD.compute(M);

            auto tp_end = high_resolution_clock::now();
            auto duration = tp_end - tp_start;
            double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
            std::cout << "Elapsed Time of EigenSolver " << duration_ms << "[ms]" << std::endl;

            if (EVD.info() != Eigen::Success)
            {
                throw std::runtime_error("Failed to compute EVD for matrix M with leaked rank.");
            }

            // 固有値は列ベクトルの形で得られる
            std::cout << "Eigen values of [λ1,λ2,...] = \n"
                      << EVD.eigenvalues() << std::endl;

            // 固有ベクトルは行列として得られる(列ベクトルが各固有ベクトルであり, 固有値に対応)
            std::cout << "Eigen vectors of [v1,v2,...] = \n"
                      << EVD.eigenvectors() << std::endl;
        }

        std::cout << "------------------" << std::endl;

        // 3. 複素行列(非正方でOK) : 優決定系,劣決定系,ランク落ち -> ComplexEigenSolver
        {
            Eigen::Matrix3d M;
            M << 1, 2, 2, 0, 1, 1, 0, 0, 0;
            std::cout << "M = \n"
                      << M << std::endl;
            CheckRank(M);

            Eigen::ComplexEigenSolver<Eigen::Matrix3d> CEVD;

            auto tp_start = high_resolution_clock::now();

            CEVD.compute(M);

            auto tp_end = high_resolution_clock::now();
            auto duration = tp_end - tp_start;
            double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
            std::cout << "Elapsed Time of EigenSolver " << duration_ms << "[ms]" << std::endl;

            if (CEVD.info() != Eigen::Success)
            {
                throw std::runtime_error("Failed to compute EVD for matrix M with leaked rank.");
            }

            // 固有値は列ベクトルの形で得られる
            std::cout << "Eigen values of [λ1,λ2,...] = \n"
                      << CEVD.eigenvalues() << std::endl;

            // 固有ベクトルは行列として得られる(列ベクトルが各固有ベクトルであり, 固有値に対応)
            std::cout << "Eigen vectors of [v1,v2,...] = \n"
                      << CEVD.eigenvectors() << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}