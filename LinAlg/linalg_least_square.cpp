/**
 * @file linalg_least_square.cpp
 * @author Shinichi Inoue (inoue.shinichi.1800@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <test_utils.hpp>

/**
 * @brief 最小二乗法 min ||Ax-b||L2 -> x
 * @note 連立1次方程式を minimun ||x||L2 として近似解xを求める方法. 
 * @note 解の個数に対してノイズが乗った解の個数以上ある任意の行数の方程式に有効.
 * @note 解のノイズを最小化する近似解xが求まる. その際, 係数行列Aの一般逆行列はムーアペンローズの疑似逆行列になる.
 * @note 係数行列が列フルランクor行フルランクであれば, QR系で解けるが, 現実問題行列Aに関する特性がわからないので, SVDで解く.
 */

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

namespace Eigen
{
    typedef Eigen::Matrix<double, 15, 1> Vector15d;
    typedef Eigen::Matrix<double, 20, 1> Vector20d;
}

int main(int, char**)
{
    try
    {
        // 優決定系(列フルランク)  for least square
        {
            // -> ColPivHouseholderQR
            {
                // Ax=bの解法と同じ
            }

            // -> FullPivHouseholderQR
            {
                // Ax=bの解法と同じ
            }
        }

        std::cout << "------------------" << std::endl;

        // 劣決定系(行フルランク)
        {
            // -> ColPivHouseholderQR
            {
                // Ax=bの解法と同じ
            }

            // -> FullPivHouseholderQR
            {
                // Ax=bの解法と同じ
            }
        }

        std::cout << "------------------" << std::endl;

        // ランク落ち
        {
            // Ax=bの解法と同じだが, 一応解いておく
            
            // -> JacobiSVD
            {
                Eigen::MatrixXd A(20, 15); // 動的サイズ行列.後で初期化.
                Eigen::Vector20d b;
                Eigen::Vector15d x;

                // 係数行列Aのセット
                // 係数行列のセット
                A = Eigen::MatrixXd::Random(20, 15);
                std::cout << "A = \n" << A << std::endl;

                CheckRank(A);

                // ベクトルbのセット
                b = Eigen::Vector20d::Random();
                std::cout << "b = \n" << b << std::endl;

                // JacobiSVD を使った特異値分解 (行列サイズが10を超えているので遅い)
                Eigen::JacobiSVD JSVD(A, Eigen::ComputeThinU | Eigen::ComputeThinV);

                auto tp_start = high_resolution_clock::now();

                x = JSVD.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of JacobiSVD " << duration_ms << "[ms]" << std::endl;

                std::cout << "Least squared x = \n" << x << std::endl;
            }

            // -> BDCSVD
            {
                Eigen::MatrixXd A(20, 15); // 動的サイズ行列.後で初期化.
                Eigen::Vector20d b;
                Eigen::Vector15d x;

                // 係数行列Aのセット
                // 係数行列のセット
                A = Eigen::MatrixXd::Random(20, 15);
                std::cout << "A = \n"
                          << A << std::endl;

                CheckRank(A);

                // ベクトルbのセット
                b = Eigen::Vector20d::Random();
                std::cout << "b = \n"
                          << b << std::endl;

                // BDCSVD を使った特異値分解 (行列サイズが10を超えているのでものすごく遅い)
                Eigen::BDCSVD BDCSVD(A, Eigen::ComputeThinU | Eigen::ComputeThinV);

                auto tp_start = high_resolution_clock::now();

                x = BDCSVD.solve(b);

                auto tp_end = high_resolution_clock::now();
                auto duration = tp_end - tp_start;
                double duration_ms = duration_cast<nanoseconds>(duration).count() / 1000.0;
                std::cout << "Elapsed Time of BDCSVD " << duration_ms << "[ms]" << std::endl;

                std::cout << "Least squared x = \n"
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
