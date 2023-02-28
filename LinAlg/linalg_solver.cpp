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

/**
 * @brief 連立方程式Ax=bの解法一覧
 * 1. 決定系(Aがフルランク. 正則行列) -> ガウスの消去法(ColPivLU, FullPivLU, LLT, LTDT). 最小二乗法(QR系, SVD系でも解ける).
 * 2. 優決定系(Aが列フルランク. 列に関して正則. 最小二乗法で近似解を解く) -> HouseholderQR, ColPivHouseholderQR, FullPivHouseholerQR, BDCSVD, JacobiSVD
 * 3. 劣決定系(Aが行フルランク. 行に関して正則. L2ノルム正則によるラグランジュ未定乗数法で任意の解から1つ選ぶ. 結局, 最小二乗法で解く方法と同じになる.) -> BDCSVD, JacobiSVD
 * 4. ランク落ち(rank(A) = r < min(m,n)) -> 1,2,3のどれかに帰着するので, SVD系でOK.
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