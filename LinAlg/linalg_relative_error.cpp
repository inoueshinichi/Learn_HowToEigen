/**
 * @file linalg_relative_error.cpp
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
 * @brief 連立一次方程式に関する相対誤差(L2ノルムの場合で, 条件数に一致)
 * @note Eigenに関数はないので, 自分で計算する.
 * @note double relative_error = (A*x - b).norm() / b.norm(); // norm() is L2 norm
 */

int main(int, char**)
{
    try
    {
        Eigen::MatrixXd A = Eigen::MatrixXd::Random(100, 100);
        Eigen::MatrixXd b = Eigen::MatrixXd::Random(100, 50);
        Eigen::MatrixXd x = A.fullPivLu().solve(b);
        double relative_error = (A * x - b).norm() / b.norm(); // norm() is L2 norm
        std::cout << "The relative error is:\n"
                  << relative_error << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
