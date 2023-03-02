/**
 * @file general_inverse_matrix.cpp
 * @author Shinichi Inoue (inoue.shinichi.1800@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <test_utils.hpp>

/**
 * @brief 一般逆行列の求め方. 行列M(mxn)
 * @note 直接一般逆行列を求めるようなことはせず, [1]連立1次方程式の解から求める or [2]SVDから直接式を求める.
 * @note 行列M(mxn)がフルランク以外はSVD系を使っとけば安心. ただし, JacobiSVDは, 行列サイズが10未満で使用すること.
 * @note 行列M(mxn)の条件がわからない環境では, 実質的にBDCSVD一択.
 * 1. フルランク(正則行列) rank(M) = m = n
 * 1-1. 実行列 -> EVD系, LU系, QR系, SVD系. 推奨はPartialPivLU.
 * 1-2. 複素行列 -> QR系, [EVD系, SVD系]
 * 1-3. 実対称行列or自己随伴行列 -> SelfAdjointEigenSolver, [LU系, QR系, EVD系, SVD系]
 *
 * 2. 優決定系(列方向に関して正則) rank(M) = n
 * 2-1. 実行列 -> EVD系, QR系, SVD系.  推奨はColPivHouseholderQR or SVD系
 * 2-2. 複素行列 -> EVD系, QR系, SVD系. 推奨はColPivHouseholderQR or SVD系
 *
 * 3. 劣決定系 rank(M) = m
 * 3-1. 実行列 -> EVD系, SVD系. 推奨はSVD系
 * 3-2. 複素行列 -> EVD系, SVD系. 推奨はSVD系
 * 3-3. 実対称行列or自己随伴行列 -> SelfAdjointEigenSolver, EVD系, SVD系. 推奨はSelfAdjointEigenSolver
 */

namespace Eigen
{
    typedef Eigen::Matrix<double, 6, 1> Vector6d;
    typedef Eigen::Matrix<double, 6, 6> Matrix6d;
}



template <typename MAT>
void CheckRank(const MAT& mat)
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


// 1. ランク落ちの実対称行列(6x6, rank=5)
Eigen::Matrix6d M_1;   // 対象の行列 M_1 = UΣU^{T}で表せるとき
Eigen::Matrix6d M_1_i; // 一般逆行列 M_1_i = UΣ^{-1}U^{T}

// 2. ランク落ちの実正方行列(3x3, m=3,n=3 rank=r=n < m)
Eigen::Matrix3d M_2;   // 対称の行列
Eigen::Matrix3d M_2_i; // 一般逆行列

int main(int, char**)
{
    try
    {
        // 1. 行列Mが実対称正方行列(nxn)のとき(rank(M) = r < n) (ランク落ち)
       {
            // ランク 5 の対称行列作成
            Eigen::Matrix6d T, T2;
            T = Eigen::Matrix6d::Random();
            T2 = (T + T.transpose()) / 2.0; // 対象化
            T = T * T.transpose(); // 正値化
            Eigen::SelfAdjointEigenSolver<Eigen::Matrix6d> ES(T);
            M_1 = Eigen::Matrix6d::Zero(); // 零行列に初期化
            // rank(M) = 5 < 6
            for (int i = 1; i < 6; ++i)
            {
                // 対角化の逆操作 (最大固有値を省いてランク5の行列を作る)
                M_1 += ES.eigenvectors().col(i) * ES.eigenvectors().col(i).transpose() * ES.eigenvalues()(i);
            }
            std::cout << "Original matrix M_1 (ランク落ちの実対称行列 rank(M_1)=5) = \n"
                      << M_1 << std::endl;

            // ランク落ちの実対称行列の一般逆行列を求める
            if (M_1.cols() != M_1.rows())
            {
                std::abort(); // 正方でない
            }

            int n = M_1.cols();
            ES.compute(M_1); // SelfAdjointEigenSolver

            if (ES.info() != Eigen::Success)
            {
                std::abort();
            }

            M_1_i = Eigen::Matrix6d::Zero();
            int r = 5; // ランク5

            // 一般逆行列の計算
            for (int i = n - r; i < n; i++) // 6-5=1
            {
                // 実対称行列を作成する際に使用しなかった最大固有値と固有ベクトルを使う.
                // M_1_i = U * Σ^{-1} * U^{T}の別計算方法.
                M_1_i += ES.eigenvectors().col(i) * ES.eigenvectors().col(i).transpose() / ES.eigenvalues()(i);
            }

            std::cout << "General Inverse Matrix with rank = 5 \n" << M_1_i << std::endl;
        }

        std::cout << "------------------------------" << std::endl;

        /**
         * @brief EigenSolverで一般逆行列を求めるのは無理っぽい
         *
         */
        // // 2. 行列Mがランク落ち実正方行列(nxn)のとき
        // {
        //     // EigenはC言語の標準ライブラリのsrand()関数をランダムジェネレータに使用している.
        //     //#include <stdlib.h>
        //     srand(100);
        //     M_2 << 1, 2, 2, 0, 1, 1, 0, 0, 0;
        //     std::cout << "M_2 = \n" << M_2 << std::endl;
        //     CheckRank(M_2);

        //     auto tp_start = high_resolution_clock::now();

        //     Eigen::EigenSolver<Eigen::Matrix4d> ES(M_2, true); // 固有値ベクトルの計算ON

        //     auto tp_end = high_resolution_clock::now();
        //     auto duration = tp_end - tp_start;
        //     double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
        //     std::cout << "Elapsed Time of EigenSolver " << duration_ms << "[ms]" << std::endl;

        //     if (ES.info() != Eigen::Success)
        //     {
        //         std::abort();
        //     }

        //     /**
        //      * @brief ムーアペンローズの擬似逆行　
        //      * @note M_2 = V * D * V^{-1}と分解してるから
        //      * 擬似逆行列は M_2_i = V * D^{-1} * V^{-1}
        //      */
        //     Eigen::Matrix4d D = ES.pseudoEigenvalueMatrix(); 
        //     Eigen::Matrix4d V = ES.pseudoEigenvectors(); 

        //     std::cout << "psedoEigenvalueMatrix D = \n" << D << std::endl;
        //     std::cout << "pseudoEigenvectors V = \n" << V << std::endl;
        //     std::cout << "---" << std::endl;
        //     std::cout << "V*D*V^{-1} = \n"
        //               << V * D * V.inverse() << std::endl;
        // }

        /**
         * @brief FullPivHouseholderQRで一般逆行列を求めるのは無理っぽい
         * 
         */
        // // 2. 行列Mがランク落ち実正方行列(nxn)のとき
        // {
        //     // ランク落ち実正方行列
        //     M_2 << 1, 2, 2, 0, 1, 1, 0, 0, 0;
        //     std::cout << "M_2 = \n"
        //               << M_2 << std::endl;
        //     CheckRank(M_2);

        //     auto tp_start = high_resolution_clock::now();

        //     Eigen::FullPivHouseholderQR<Eigen::Matrix4d> FPHQR(M_2); // 固有値ベクトルの計算ON

        //     auto tp_end = high_resolution_clock::now();
        //     auto duration = tp_end - tp_start;
        //     double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
        //     std::cout << "Elapsed Time of EigenSolver " << duration_ms << "[ms]" << std::endl;

        //     std::cout << "IsInvertable of A=QR :" << std::boolalpha << FPHQR.isInvertible() << std::endl;

        //     if (FPHQR.isInvertible())
        //     {
        //         std::cout << "Inverse of A=QR : = \n"
        //                   << FPHQR.inverse() << std::endl;
        //     }
        // }

        /**
         * @brief 一般逆行列はSVDで求める. 
         * 
         */
        // 2. 行列Mがランク落ち実正方行列(nxn)のとき
        {
            // ランク落ち実正方行列
            M_2 << 1, 2, 2, 0, 1, 1, 0, 0, 0;
            std::cout << "M_2 = \n"
                      << M_2 << std::endl;
            CheckRank(M_2);

            auto tp_start = high_resolution_clock::now();

            Eigen::BDCSVD<Eigen::Matrix3d> BDC_SVD(M_2, Eigen::ComputeThinU | Eigen::ComputeThinV); // 固有値ベクトルの計算ON

            auto tp_end = high_resolution_clock::now();
            auto duration = tp_end - tp_start;
            double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
            std::cout << "Elapsed Time of BDCSVD " << duration_ms << "[ms]" << std::endl;

            // 特異値は降順で配列に格納されている
            std::cout << "Singular Value = \n"
                      << BDC_SVD.singularValues() << std::endl;

            // 直交行列U
            std::cout << "U = \n"
                      << BDC_SVD.matrixU() << std::endl;
            // 直交行列V
            std::cout << "V = \n"
                      << BDC_SVD.matrixV() << std::endl;

            /**
             * @brief 一般逆行列
             * SVDで M_2 = U * Σ * V^{-1} と計算されるので,
             * M_2_i = V * Σ^{-1} * U^{-1} で計算できる.
             */
            M_2_i = BDC_SVD.matrixV() * BDC_SVD.singularValues().asDiagonal().inverse() * BDC_SVD.matrixU().transpose();

            // 同じ計算
            // Eigen::VectorXd s = BDC_SVD.singularValues();
            // s = s.array().inverse();
            // M_2_i = BDC_SVD.matrixV() * s.asDiagonal() * BDC_SVD.matrixU().transpose();

            std::cout << "M_2_i = \n" << M_2_i << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
