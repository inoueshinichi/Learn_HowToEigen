/**
 * @file svd_decomp.cpp
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
 * @brief 特異値分解(SVD)
 * @note
 * M = UΣV^T
 * Mは正方行列(nxm). UとVは直行行列. Σは対角行列.
 * Σの対角成分が特異値.
 * U(nxl), Σ(lxl), V(mxl)
 * UΣV^T = (n,l) @ (l,l) @ (l,m) = (n,m) (※M)
 * 次元lはnとmの小さい方と同じ次元となる.
 *
 * @warning JacobiSVDクラスを使う. オプション指定しないとΣのみしか計算しない.
 * @warning 非対称行列の場合とで, オプション指定が異なる.
 * @warning 特異値は固有値とは異なり, 降順で配列に格納されている.
 *
 * @return int
 */

int main(int, char **)
{
    try
    {
        // BDCSVD
        // 行列Mが(nxn)の対称行列の場合
        {
            Eigen::Matrix3d M;
            M << 1.0, 0.5, 2.3,
                0.5, 0.9, -1.6,
                2.3, -1.6, 4.8;
            std::cout << "M(3x3) = \n"
                      << M << std::endl;

            auto tp_start = high_resolution_clock::now();

            // 特異値分解
            // Eigen::BDCSVD SVD(M); // 何も指定しないと特異値行列Σの対角要素だけ計算
            Eigen::BDCSVD SVD(M, Eigen::ComputeFullU | Eigen::ComputeFullV);

            auto tp_end = high_resolution_clock::now();
            auto duration = tp_end - tp_start;
            double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
            std::cout << "Elapsed Time of BDCSVD " << duration_ms << "[ms]" << std::endl;

            // 特異値は降順で配列に格納されている
            std::cout << "Singular Value of M = \n"
                      << SVD.singularValues() << std::endl;

            // 直交行列U
            std::cout << "U(3x3) of M = \n"
                      << SVD.matrixU() << std::endl;
            // 直交行列V
            std::cout << "V(3x3) of M = \n"
                      << SVD.matrixV() << std::endl;

            // 元に戻るか計算
            Eigen::Matrix3d StructM;
            StructM = SVD.matrixU() * SVD.singularValues().asDiagonal() * SVD.matrixV().transpose();

            std::cout << "Struct M(3x3) = \n"
                      << StructM << std::endl;
        }

        std::cout << "----------------------------" << std::endl;

        // BDCSVD
        // 行列Mが(mxn)の非対称行列の場合
        {
            // 非対称行列は動的型である必要がある.
            Eigen::MatrixXd M = Eigen::MatrixXd::Random(3, 2); // M(3,2)

            std::cout << "M(3x2) = \n"
                      << M << std::endl;

            auto tp_start = high_resolution_clock::now();

            // 特異値分解
            Eigen::BDCSVD SVD(M, Eigen::ComputeThinU | Eigen::ComputeThinV);

            auto tp_end = high_resolution_clock::now();
            auto duration = tp_end - tp_start;
            double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
            std::cout << "Elapsed Time of BDCSVD " << duration_ms << "[ms]" << std::endl;

            // 特異値は降順で配列に格納されている
            std::cout << "Singular Value of M = \n"
                      << SVD.singularValues() << std::endl;

            // 直交行列U
            std::cout << "U(3x2) of M = \n"
                      << SVD.matrixU() << std::endl;
            // 直交行列V
            std::cout << "V(2x2) of M = \n"
                      << SVD.matrixV() << std::endl;

            Eigen::MatrixXd StructM;
            StructM = SVD.matrixU() * SVD.singularValues().asDiagonal() * SVD.matrixV().transpose();

            std::cout << "Struct M(3x2) = \n"
                      << StructM << std::endl;
        }

        std::cout << "----------------------------" << std::endl;

        // JacobiSVD
        // 行列Mが(nxn)の対称行列の場合
        {
            Eigen::Matrix3d M;
            M << 1.0, 0.5, 2.3,
                0.5, 0.9, -1.6,
                2.3, -1.6, 4.8;
            std::cout << "M(3x3) = \n"
                      << M << std::endl;

            auto tp_start = high_resolution_clock::now();

            // 特異値分解
            // Eigen::JacobiSVD SVD(M); // 何も指定しないと特異値行列Σの対角要素だけ計算
            Eigen::JacobiSVD SVD(M, Eigen::ComputeFullU | Eigen::ComputeFullV);

            auto tp_end = high_resolution_clock::now();
            auto duration = tp_end - tp_start;
            double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
            std::cout << "Elapsed Time of JacobiSVD " << duration_ms << "[ms]" << std::endl;

            // 特異値は降順で配列に格納されている
            std::cout << "Singular Value of M = \n" << SVD.singularValues() << std::endl;

            // 直交行列U
            std::cout << "U(3x3) of M = \n" << SVD.matrixU() << std::endl;
            // 直交行列V
            std::cout << "V(3x3) of M = \n" << SVD.matrixV() << std::endl;

            // 元に戻るか計算
            Eigen::Matrix3d StructM;
            StructM = SVD.matrixU() * SVD.singularValues().asDiagonal() * SVD.matrixV().transpose();

            std::cout << "Struct M(3x3) = \n" << StructM << std::endl;
        }

        std::cout << "----------------------------" << std::endl;
        
        // JacobiSVD
        // 行列Mが(nxm)の非対称行列の場合
        {
            // 非対称行列は動的型である必要がある.
            Eigen::MatrixXd M = Eigen::MatrixXd::Random(3, 2); // M(3,2)

            std::cout << "M(3x2) = \n"
                      << M << std::endl;

            auto tp_start = high_resolution_clock::now();

            // 特異値分解
            Eigen::JacobiSVD SVD(M, Eigen::ComputeThinU | Eigen::ComputeThinV);
       
            auto tp_end = high_resolution_clock::now();
            auto duration = tp_end - tp_start;
            double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
            std::cout << "Elapsed Time of SVD " << duration_ms << "[ms]" << std::endl;

            // 特異値は降順で配列に格納されている
            std::cout << "Singular Value of M = \n"
                      << SVD.singularValues() << std::endl;

            // 直交行列U
            std::cout << "U(3x2) of M = \n"
                      << SVD.matrixU() << std::endl;
            // 直交行列V
            std::cout << "V(2x2) of M = \n"
                      << SVD.matrixV() << std::endl;

            Eigen::MatrixXd StructM;
            StructM = SVD.matrixU() * SVD.singularValues().asDiagonal() * SVD.matrixV().transpose();

            std::cout << "Struct M(3x2) = \n"
                      << StructM << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}