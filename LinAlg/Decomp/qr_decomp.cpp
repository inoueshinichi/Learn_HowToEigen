/**
 * @file qr_decomp.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <test_utils.hpp>

/**
 * @brief QR分解
 * @note
 * M = QR (m,n) = (m,m) @ (m,n)　※ m>=n
 * 実正方行列M(mxn)を直行行列Q(mxm)と上三角行列R(mxn)に分解する.
 * 1次連立方程式の解法, 最小二乗法, 固有値問題それぞれに適用できる.
 * 最小二乗法を解く際は, 特異値分解(SVD)の方が一般的.
 * 
 * @warning QR分解は元々は固有値問題を解くQR法(ハウスホルダー法)が起源
 * 固有値問題では, n次正方行列行列A(n,n)を中間表現として下記に示す行列に変換して解く.
 * 1. 三重対角行列・・・Aが対称行列の場合
 * 2. ヘッセンベルグ行列・・・Aが非対称行列の場合
 *
 * @warning 様々な手法がある.
 * ・ギブンス回転
 * ・ハウスホルダー変換
 * ・グラムシュミットの正規直交化法(グラムシュミット分解)
 *
 * @warning Eigenではハウスホルダー変換を使う
 * 1. HouseholderQR
 * 2. ColPivHouseholderQR
 * 3. FullPivHouseholderQR
 */



int main(int, char**)
{
    try
    {
        // HouseholderQR
        {
            Eigen::Matrix3d M;
            M << 5.0, 1.0, -2.0,
                1.0, 6.0, -1.0,
                2.0, -1.0, 5.0;

            std::cout << "M = \n"
                      << M << std::endl;

            auto tp_start = high_resolution_clock::now();

            // ハウスホルダーQR分解
            Eigen::HouseholderQR<Eigen::Matrix3d> HQR;

            HQR.compute(M); // 計算

            auto tp_end = high_resolution_clock::now();
            auto duration = tp_end - tp_start;
            double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
            std::cout << "Elapsed Time of Householder_QR " << duration_ms << "[ms]" << std::endl;

            std::cout << "QR = \n" << HQR.matrixQR() << std::endl;

            Eigen::MatrixXd Q;
            Q = HQR.householderQ();
            std::cout << "Complete unitary Q = \n"
                      << Q << std::endl;

            using SeqQ = Eigen::HouseholderSequence<Eigen::Matrix3d, Eigen::Vector3d>;
            SeqQ seqQ = HQR.householderQ();
            Eigen::Index length_of_householder_transform_sequence;
            length_of_householder_transform_sequence = seqQ.length();
            std::cout << "Num Householder Transform Op " << length_of_householder_transform_sequence << std::endl;

            Eigen::MatrixXd thinQ(Eigen::MatrixXd::Identity(3, 3));
            for (size_t i = 0; i < length_of_householder_transform_sequence; ++i)
            {
                thinQ = HQR.householderQ() * thinQ;
                std::cout << "Thin(" << i << ") = \n" << thinQ << std::endl;
            }
        }

        std::cout << "----------------------------" << std::endl;

        // ColPivHouseholderQR
        {
            Eigen::Matrix3d M;
            M << 5.0, 1.0, -2.0,
                1.0, 6.0, -1.0,
                2.0, -1.0, 5.0;

            std::cout << "M = \n"
                      << M << std::endl;

            auto tp_start = high_resolution_clock::now();

            // ColPiv ハウスホルダーQR分解
            Eigen::ColPivHouseholderQR<Eigen::Matrix3d> HQR;

            HQR.compute(M); // 計算

            auto tp_end = high_resolution_clock::now();
            auto duration = tp_end - tp_start;
            double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
            std::cout << "Elapsed Time of ColPiv-Householder_QR " << duration_ms << "[ms]" << std::endl;

            if (HQR.info() != Eigen::Success)
            {
                std::cout << "Failed ColPivHouseholderQR" << std::endl;
                std::abort(); // 失敗したら終了
            }

            std::cout << "Rank of QR = " << HQR.rank() << std::endl;

            std::cout << "QR = \n"
                          << HQR.matrixQR() << std::endl;

            if (HQR.isInvertible())
            {
                std::cout << "QR_inv = \n"
                          << HQR.inverse() << std::endl;

                std::cout << "QR*QR_inv = \n"
                          << HQR.matrixQR() * HQR.inverse() << std::endl;
                std::cout << "ほぼ単位行列" << std::endl;
            }

            // matrixR()の出力の右上三角行列のみRであり意味がある. 
            Eigen::MatrixXd R = HQR.matrixR().triangularView<Eigen::Upper>();
            std::cout << "R = \n" << R << std::endl;

            Eigen::MatrixXd Q;
            Q = HQR.householderQ();
            std::cout << "Complete unitary Q = \n"
                      << Q << std::endl;

            std::cout << "Q*R = \n" << Q * R << std::endl;

            using SeqQ = Eigen::HouseholderSequence<Eigen::Matrix3d, Eigen::Vector3d>;
            SeqQ seqQ = HQR.householderQ();
            Eigen::Index length_of_householder_transform_sequence;
            length_of_householder_transform_sequence = seqQ.length();
            std::cout << "Num Householder Transform Op " << length_of_householder_transform_sequence << std::endl;

            Eigen::MatrixXd thinQ(Eigen::MatrixXd::Identity(3, 3));
            for (size_t i = 0; i < length_of_householder_transform_sequence; ++i)
            {
                thinQ = HQR.householderQ() * thinQ;
                std::cout << "Thin(" << i << ") = \n"
                          << thinQ << std::endl;
            }
        }

        std::cout << "----------------------------" << std::endl;

        // FullPivHouseholderQR
        {
            Eigen::Matrix3d M;
            M << 5.0, 1.0, -2.0,
                1.0, 6.0, -1.0,
                2.0, -1.0, 5.0;

            std::cout << "M = \n"
                      << M << std::endl;

            auto tp_start = high_resolution_clock::now();

            // FullPiv ハウスホルダーQR分解
            Eigen::FullPivHouseholderQR<Eigen::Matrix3d> HQR;

            HQR.compute(M); // 計算

            auto tp_end = high_resolution_clock::now();
            auto duration = tp_end - tp_start;
            double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
            std::cout << "Elapsed Time of FullPiv-Householder_QR " << duration_ms << "[ms]" << std::endl;

            std::cout << "Rank of QR = " << HQR.rank() << std::endl;

            std::cout << "QR = \n"
                      << HQR.matrixQR() << std::endl;

            if (HQR.isInvertible())
            {
                std::cout << "QR_inv = \n"
                          << HQR.inverse() << std::endl;

                std::cout << "QR*QR_inv = \n"
                          << HQR.matrixQR() * HQR.inverse() << std::endl;
                std::cout << "ほぼ単位行列" << std::endl;
            }

            // // matrixR()の出力の右上三角行列のみRであり意味がある.
            // Eigen::MatrixXd R = HQR.matrixR().triangularView<Eigen::Upper>();
            // std::cout << "R = \n"
            //           << R << std::endl;

            Eigen::MatrixXd Q;
            Q = HQR.matrixQ();
            std::cout << "Complete unitary Q = \n"
                      << Q << std::endl;

            // std::cout << "Q*R = \n"
            //           << Q * R << std::endl;

            // using SeqQ = Eigen::HouseholderSequence<Eigen::Matrix3d, Eigen::Vector3d>;
            // SeqQ seqQ = HQR.householderQ();
            // Eigen::Index length_of_householder_transform_sequence;
            // length_of_householder_transform_sequence = seqQ.length();
            // std::cout << "Num Householder Transform Op " << length_of_householder_transform_sequence << std::endl;

            // Eigen::MatrixXd thinQ(Eigen::MatrixXd::Identity(3, 3));
            // for (size_t i = 0; i < length_of_householder_transform_sequence; ++i)
            // {
            //     thinQ = HQR.householderQ() * thinQ;
            //     std::cout << "Thin(" << i << ") = \n"
            //               << thinQ << std::endl;
            // }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}