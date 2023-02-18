/**
 * @file cholesky_decomp.cpp
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
 * @brief コレスキー分解
 * @note
 * M = LL^{T}
 * 正値実対称行列Mを下三角行列Lに分解する方法.
 * M (nxn), 成分は実数 任意のベクトルxに対してxMx>0 (正値).
 * すなわち, Mの全固有値λ>0
 * 
 * #include <Eigen/Cholesky>が必要.
 */

int main(int, char**)
{
    try
    {
        // LLT法(計算コスト小, 精度低)
        {
            Eigen::Matrix3d M;

            // 行列に値を代入 (正値対称行列)
            M << 5.0, 1.0, -2.0,
                1.0, 6.0, -1.0,
                -2.0, -1.0, 5.0;

            std::cout << "M = \n"
                      << M << std::endl;

            auto tp_start = high_resolution_clock::now();

            // コレスキー分解(LLT)
            Eigen::LLT<Eigen::Matrix3d> CholD(M);

            // 行列 L
            Eigen::Matrix3d L = CholD.matrixL();

            auto tp_end = high_resolution_clock::now();
            auto duration = tp_end - tp_start;
            double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
            std::cout << "Elapsed Time of Cholesky(LLT) " << duration_ms << "[ms]" << std::endl;

            std::cout << "L = \n"
                      << L << std::endl;

            // 元の行列になるかを確認 Matrix3d
            Eigen::Matrix3d StructM;
            StructM = L * L.transpose();

            std::cout << "StructM = \n" << StructM << std::endl;
        }

        std::cout << "----------------------------" << std::endl;

        // LDLT法(計算コスト大, 精度高)
        {
            Eigen::Matrix3d M;

            // 行列に値を代入 (正値対称行列)
            M << 5.0, 1.0, -2.0,
                1.0, 6.0, -1.0,
                -2.0, -1.0, 5.0;

            std::cout << "M = \n"
                      << M << std::endl;

            auto tp_start = high_resolution_clock::now();

            // コレスキー分解(LDLT)
            Eigen::LDLT<Eigen::Matrix3d> CholD(M);

            // 行列 L
            Eigen::Matrix3d L = CholD.matrixL();

            auto tp_end = high_resolution_clock::now();
            auto duration = tp_end - tp_start;
            double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
            std::cout << "Elapsed Time of Cholesky(LDLT) " << duration_ms << "[ms]" << std::endl;

            std::cout << "L = \n"
                      << L << std::endl;

            // 元の行列になるかを確認 Matrix3d
            Eigen::Matrix3d StructM;
            StructM = L * L.transpose();

            std::cout << "StructM = \n"
                      << StructM << std::endl;
        }

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}