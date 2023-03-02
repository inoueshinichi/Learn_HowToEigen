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

int main(int, char**)
{
    try
    {
        /* code */
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
