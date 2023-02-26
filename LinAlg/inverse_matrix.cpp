/**
 * @file inverse_matrix.cpp
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
 * @brief 逆行列の計算.
 * @note
 *
 * @warning 4x4程度の正則行列ならinverse()は有効.
 * それ以外の大きな正則行列は, LU分解(PartialPivLU)を用いて計算する.
 * ただし, 行列が正則であることが条件.
 *
 * 一般にA(m,n)のランクによって解法が変わる.
 * 1. rank(A) = m = n : 決定系 -> inverse()(直接法) or LU分解(PartialPivLU)のsolver()を使う.
 * 2. rank(A) = n : 優決定系 -> QR分解(ColPivHouseholderQR)のsolver()を使う
 * 3. rank(A) = m : 劣決定系 -> SVD()  ※Lagurange未定乗数法でもOKだが普通しない
 * 4. rank(A) = r < min(m,n) : ランク落ち -> SVD(BDCSVD)のsolver()を使う
 *
 * #include <Eigen/LU>が必要.
 *
 * @return int
 */

int main(int, char **)
{
    try
    {
        // 行列式と逆行列
        {
            Eigen::Matrix3d M; // 3x3
            M << 1.0, 0.5, 2.3,
                -4.8, 0.9, -1.6,
                3.2, -0.6, -3.7;

            std::cout << "M = \n"
                      << M << std::endl;

            std::cout << "Det(M) = " << M.determinant() << std::endl; // 行列式
            std::cout << "Inv(M) = " << M.inverse() << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}