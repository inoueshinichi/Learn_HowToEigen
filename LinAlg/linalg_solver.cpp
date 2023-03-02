/**
 * @file linalg_solver.cpp
 * @author Shinichi Inoue (inoue.shinichi.1800@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <test_utils.hpp>

#include <cstdlib> // srand

/**
 * @brief 連立方程式Ax=bの解法一覧 M(mxn)
 * 1. 決定系: Aがフルランク, rank(M)=m=n  -> ガウスの消去法(LU系◎, Cholesky系), 完全直交化(CompleteOrthgonalDecomposition), 最小二乗法(QR系, SVD系).
 * 2. 優決定系: Aが列フルランク. rank(M)=n -> ガウスの消去法(FullPivLU), 最小二乗法(QR系, SVD系), COD(CompleteOrthgonalDecomposition).
 * 3. 劣決定系: Aが行フルランク. rank(M)=m -> L2ノルム正則を目的関数, s.tをAx=bとしたラグランジュ未定乗数法で任意の解から1つ選ぶ. -> 帰着: 最小二乗法法 -> QR系, SVD系
 * 4. ランク落ち: rank(A)=r<min(m,n)     -> 1,2,3のどれかに帰着するのでSVD系.
 * 
 * @note 優決定or劣決定の行か列の一方がフルランクの場合QR系が使えそう. もちろん, SVD系も使える
 */

namespace Eigen
{
    typedef Eigen::Matrix<double, 6, 1> Vector6d;
    typedef Eigen::Matrix<double, 6, 6> Matrix6d;
}

// ランクチェック by FullPivLS
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

int main(int, char**)
{
    try
    {
        // 1. 決定系 いろんな解き方ができる
        {
            Eigen::Matrix6d M;
            std::srand(1234);
            M = Eigen::Matrix6d::Random();
            std::cout << "M = \n" << M << std::endl;
            CheckRank(M);

            Eigen::Vector6d x, b;
            x = Eigen::Vector6d::Zero();
            b = Eigen::Vector6d::Random();
            std::cout << "x = \n" << x << std::endl;
            std::cout << "b = \n" << b << std::endl;

            std::cout << "----- Let's solve Ax=b [Full Rank]-----" << std::endl;

            // 1-1. PartialPivLU
            {
                std::cout << "[PartialPivLU solver]" << std::endl;
                Eigen::PartialPivLU<Eigen::Matrix6d> PPLU(M);

                auto tp_start = high_resolution_clock::now();

                x = PPLU.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of PartialPivLU " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n" << x << std::endl;
            }

            std::cout << "------------" << std::endl;

            // 1-2. FullPivLU
            {
                std::cout << "[FullPivLU solver]" << std::endl;
                Eigen::FullPivLU<Eigen::Matrix6d> FPLU(M);

                auto tp_start = high_resolution_clock::now();

                x = FPLU.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of FullPivLU " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }

            std::cout << "------------" << std::endl;

            // 1-3. ColPivHouseholderQR
            {
                std::cout << "[ColPivHouseholderQR solver]" << std::endl;
                Eigen::ColPivHouseholderQR<Eigen::Matrix6d> CPQR(M);

                auto tp_start = high_resolution_clock::now();

                x = CPQR.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of ColPivHouseholderQR " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }

            std::cout << "------------" << std::endl;

            // M = Eigen::Matrix6d::Random(); // 別の行列
            // std::cout << "M = \n"
            //           << M << std::endl;
            // CheckRank(M);

            // 1-4. FullPivHouseholderQR
            {
                std::cout << "[FullPivHouseholderQR solver]" << std::endl;
                Eigen::FullPivHouseholderQR<Eigen::Matrix6d> FPQR(M);

                auto tp_start = high_resolution_clock::now();

                x = FPQR.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of FullPivHouseholderQR " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }

            std::cout << "------------" << std::endl;

            // 1-5. CompleteOrthogonalDecomposition(完全直交化分解) AP = QTZ
            {
                std::cout << "[COD solver]" << std::endl;
                Eigen::CompleteOrthogonalDecomposition<Eigen::Matrix6d> COD(M);

                auto tp_start = high_resolution_clock::now();

                x = COD.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of COD " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }

            std::cout << "------------" << std::endl;

            // 1-6. JacobiSVD (by least square problem)
            {
                std::cout << "[JacobiSVD solver]" << std::endl;
                Eigen::JacobiSVD JSVD(M, Eigen::ComputeThinU | Eigen::ComputeThinV); // Thinでいいので, UとVの計算を行わないとSolverは不定な値を出す

                auto tp_start = high_resolution_clock::now();

                x = JSVD.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of JacobiSVD " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }

            std::cout << "------------" << std::endl;

            // 1-7. BDCSVD (by least square problem)
            {
                std::cout << "[BDCSVD solver]" << std::endl;
                Eigen::BDCSVD BDCSVD(M, Eigen::ComputeThinU | Eigen::ComputeThinV); // Thinでいいので, UとVの計算を行わないとSolverは不定な値を出す

                auto tp_start = high_resolution_clock::now();

                x = BDCSVD.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of BDCSVD " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }

            std::cout << "------------" << std::endl;

            // 1-8. 修正コレスキー分解(LDLT)
            {
                std::cout << "[LDLT solver]" << std::endl;
                Eigen::Matrix2f A, c;
                A << 2, -1, -1, 3;
                c << 1, 2, 3, 1;
                std::cout << "Here is the matrix A:\n"
                          << A << std::endl;
                std::cout << "Here is the right hand side c:\n"
                          << c << std::endl;

                auto tp_start = high_resolution_clock::now();

                Eigen::Matrix2f y = A.ldlt().solve(c);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of LDLT " << duration_ms << "[ms]" << std::endl;

                std::cout << "The solution is:\n"
                          << y << std::endl;
            }
        }

        std::cout << "----- Let's solve Ax=b [Full Rank about column]-----" << std::endl;

        // 2. 優決定系 FullPivLU, QR系, 
        {
            Eigen::Matrix3d M;
            M << 1, 2, 2, 0, 1, 1, 0, 0, 0;
            std::cout << "M = \n"
                      << M << std::endl;
            CheckRank(M);

            Eigen::Vector3d x, b;
            x = Eigen::Vector3d::Zero();
            b = Eigen::Vector3d::Random();
            std::cout << "x = \n"
                      << x << std::endl;
            std::cout << "b = \n"
                      << b << std::endl;


            // 2-1. PartialPivLU [Fail]
            {
                std::cout << "[PartialPivLU solver (Fail)]" << std::endl;
                Eigen::PartialPivLU<Eigen::Matrix3d> PPLU(M);

                auto tp_start = high_resolution_clock::now();

                x = PPLU.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of PartialPivLU " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }

            std::cout << "------------" << std::endl;

            // 2-1. FullPivLU [Success]
            {
                std::cout << "[FullPivLU solver (Success)]" << std::endl;
                Eigen::FullPivLU<Eigen::Matrix3d> FPLU(M);

                auto tp_start = high_resolution_clock::now();

                x = FPLU.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of FullPivLU " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }

            std::cout << "------------" << std::endl;

            // 2-2. ColPivHouseholderQR
            {
                std::cout << "[ColPivHouseHolder solver (Success)]" << std::endl;
                Eigen::ColPivHouseholderQR<Eigen::Matrix3d> CPHQR(M);

                auto tp_start = high_resolution_clock::now();

                x = CPHQR.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of ColPivHouseHolder " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }

            std::cout << "------------" << std::endl;

            // 2-3. FullPivHouseholderQR
            {
                std::cout << "[FullPivHouseHolder solver (Success)]" << std::endl;
                Eigen::FullPivHouseholderQR<Eigen::Matrix3d> FPHQR(M);

                auto tp_start = high_resolution_clock::now();

                x = FPHQR.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of ColPivHouseHolder " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }

            std::cout << "------------" << std::endl;

            // 2-4. CompleteOrthogonalDecomposition(完全直交化分解) AP = QTZ
            {
                std::cout << "[COD solver (Success)]" << std::endl;
                Eigen::CompleteOrthogonalDecomposition<Eigen::Matrix3d> COD(M);

                auto tp_start = high_resolution_clock::now();

                x = COD.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of COD " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }

            std::cout << "------------" << std::endl;

            // 2-5. JacobiSVD (by least square problem)
            {
                std::cout << "[JacobiSVD solver (Success)]" << std::endl;
                Eigen::JacobiSVD JSVD(M, Eigen::ComputeThinU | Eigen::ComputeThinV); // Thinでいいので, UとVの計算を行わないとSolverは不定な値を出す

                auto tp_start = high_resolution_clock::now();

                x = JSVD.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of JacobiSVD " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }

            std::cout << "------------" << std::endl;

            // 2-6. BDCSVD (by least square problem)
            {
                std::cout << "[BDCSVD solver (Success)]" << std::endl;
                Eigen::BDCSVD BDCSVD(M, Eigen::ComputeThinU | Eigen::ComputeThinV); // Thinでいいので, UとVの計算を行わないとSolverは不定な値を出す

                auto tp_start = high_resolution_clock::now();

                x = BDCSVD.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of BDCSVD " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }
        }

        std::cout << "----- Let's solve Ax=b [Full Rank about row]-----" << std::endl;

        // 3. 劣決定系 -> SVDによる最小二乗法
        {
            // 優決定の係数行列を転置
            Eigen::Matrix3d M;
            M << 1, 2, 2, 0, 1, 1, 0, 0, 0;
            M.transposeInPlace();
            std::cout << "M = \n"
                      << M << std::endl;
            CheckRank(M);

            Eigen::Vector3d x, b;
            x = Eigen::Vector3d::Zero();
            b = Eigen::Vector3d::Random();
            std::cout << "x = \n"
                      << x << std::endl;
            std::cout << "b = \n"
                      << b << std::endl;

            // 3-1. ColPivHouseholderQR [Fail]
            {
                std::cout << "[ColPivHouseHolder solver (Success)]" << std::endl;
                Eigen::ColPivHouseholderQR<Eigen::Matrix3d> CPHQR(M);

                auto tp_start = high_resolution_clock::now();

                x = CPHQR.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of ColPivHouseHolder " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }

            std::cout << "------------" << std::endl;

            // 3-2. FullPivHouseholderQR [Fail]
            {
                std::cout << "[FullPivHouseHolder solver (Success)]" << std::endl;
                Eigen::FullPivHouseholderQR<Eigen::Matrix3d> FPHQR(M);

                auto tp_start = high_resolution_clock::now();

                x = FPHQR.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of ColPivHouseHolder " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }

            std::cout << "------------" << std::endl;

            // 3-3. JacobiSVD [Success]
            {
                std::cout << "[JacobiSVD solver (Success)]" << std::endl;
                Eigen::JacobiSVD JSVD(M, Eigen::ComputeThinU | Eigen::ComputeThinV); // Thinでいいので, UとVの計算を行わないとSolverは不定な値を出す

                auto tp_start = high_resolution_clock::now();

                x = JSVD.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of JacobiSVD " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }

            std::cout << "------------" << std::endl;

            // 3-4. BDSSVD [Success]
            {
                std::cout << "[BDCSVD solver (Success)]" << std::endl;
                Eigen::BDCSVD BDCSVD(M, Eigen::ComputeThinU | Eigen::ComputeThinV); // Thinでいいので, UとVの計算を行わないとSolverは不定な値を出す

                auto tp_start = high_resolution_clock::now();

                x = BDCSVD.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of BDCSVD " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }
        }

        // 4. ランク落ち(rank(A) = r < min(m,n)) -> 1,2,3のどれかに帰着するので, SVD系でOK.
        {
            Eigen::Matrix<double, 3, 4> M;
            M << 3, 4, 6, 0, 
                 0, 7, 8, 0,
                 0, 0, 0, 0;
            std::cout << "M = \n"
                      << M << std::endl;
            CheckRank(M);

            Eigen::Vector4d x;
            Eigen::Vector3d b;
            x = Eigen::Vector4d::Zero();
            b = Eigen::Vector3d::Random();
            std::cout << "x = \n"
                      << x << std::endl;
            std::cout << "b = \n"
                      << b << std::endl;

            std::cout << "----- Let's solve Ax=b [Leak Rank about row and col]-----" << std::endl;

            // 4-1. FullPivHouseholderQR [Fail]
            {
                std::cout << "[FullPivHouseHolder solver (Fail)]" << std::endl;
                Eigen::FullPivHouseholderQR<Eigen::Matrix<double, 3, 4>> FPHQR(M);

                auto tp_start = high_resolution_clock::now();

                x = FPHQR.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of ColPivHouseHolder " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }

            // 4-2. JacobiSVD [Success]
            {
                std::cout << "[JacobiSVD solver (Success)]" << std::endl;
                Eigen::JacobiSVD JSVD(M, Eigen::ComputeThinU | Eigen::ComputeThinV); // Thinでいいので, UとVの計算を行わないとSolverは不定な値を出す

                auto tp_start = high_resolution_clock::now();

                x = JSVD.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of JacobiSVD " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }

            // 4-3. BDSSVD [Success]
            {
                std::cout << "[BDCSVD solver (Success)]" << std::endl;
                Eigen::BDCSVD BDCSVD(M, Eigen::ComputeThinU | Eigen::ComputeThinV); // Thinでいいので, UとVの計算を行わないとSolverは不定な値を出す

                auto tp_start = high_resolution_clock::now();

                x = BDCSVD.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of BDCSVD " << duration_ms << "[ms]" << std::endl;

                std::cout << "x = \n"
                          << x << std::endl;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}