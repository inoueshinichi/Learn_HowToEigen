/**
 * @file calc_order.cpp
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
 * @brief 数学的表記とプログラム的表記による計算順序の違い
 *
 *  S = [1, 0, 0, 0]
 *      [0, 2, 0, 0]
 *      [0, 0, 3, 0]
 *      [0, 0, 0, 1]
 *  列優先表記(数学的表記)
 *  R = [cos(45), -sin(45), 0, 0]
 *      [sin(45),  cos(45), 0, 0]
 *      [      0,        0, 1, 0]
 *      [      0,        0, 0, 1]
 *  T = [0, 0, 0, 0.5]
 *      [0, 0, 0, 1.0]
 *      [0, 0, 0, 2.5]
 *      [0, 0, 0,   1]
 *  行優先表記
 *  R = [ cos(45), sin(45), 0, 0]
 *      [-sin(45), cos(45), 0, 0]
 *      [       0,       0, 1, 0]
 *      [       0,       0, 0, 1]
 *  T = [  0,   0,   0, 0]
 *      [  0,   0,   0, 0]
 *      [  0,   0,   0, 0]
 *      [0.5, 1.0, 1.5, 1]
 *
 * @return int
 */

int main(int, char **)
{
    try
    {
        using RowMajorMatrix4f = Eigen::Matrix<float, 4, 4, Eigen::RowMajor>;
        using ColMajorMatrix4f = Eigen::Matrix<float, 4, 4, Eigen::ColMajor>;
        using RowMajorVector4f = Eigen::Matrix<float, 1, 4, Eigen::RowMajor>;
        using ColMajorVector4f = Eigen::Matrix<float, 4, 1, Eigen::ColMajor>;

        ///////////////////////////////////////////////
        // RowMajorData & RowMajorCalc = DirectX style
        ///////////////////////////////////////////////
        RowMajorVector4f rV, rV_new;
        RowMajorMatrix4f rS, rR, rT, rM;
        rV << 1.f, 1.f, 1.f, 1.f; // (1,1,1,1)
        rS << 1.f, 0.f, 0.f, 0.f,
            0.f, 2.f, 0.f, 0.f,
            0.f, 0.f, 3.f, 0.f,
            0.f, 0.f, 0.f, 1.f;
        rR << cosf(M_PI_4), sinf(M_PI_4), 0.f, 0.f,
            -sinf(M_PI_4), cosf(M_PI_4), 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f;
        rT << 0.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 0.f, 0.f,
            0.5f, 1.0f, 1.5f, 1.0f;

        rM = rS * rR * rT;
        rV_new = rV * rM;

        std::printf("--- RowMajorData & RowMajorCalc = DirectX style ---\n");
        std::cout << "rV_new " << rV_new << std::endl;

        ///////////////////////////////////////////////
        // ColMajorData & ColMajorCalc = OpenGL style
        ///////////////////////////////////////////////
        ColMajorVector4f cV, cV_new;
        ColMajorMatrix4f cS, cR, cT, cM;
        cV << 1.f, 1.f, 1.f, 1.f; // (1,1,1,1)^T
        cS << 1.f, 0.f, 0.f, 0.f,
            0.f, 2.f, 0.f, 0.f,
            0.f, 0.f, 3.f, 0.f,
            0.f, 0.f, 0.f, 1.f;
        cR << cosf(M_PI_4), -sinf(M_PI_4), 0.f, 0.f,
            sinf(M_PI_4), cosf(M_PI_4), 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f;
        cT << 0.f, 0.f, 0.f, 0.5f,
            0.f, 0.f, 0.f, 1.f,
            0.f, 0.f, 0.f, 1.5f,
            0.f, 0.f, 0.f, 1.0f;

        cM = cT * cR * cS;
        cV_new = cM * cV;

        std::printf("--- ColMajorData & ColMajorCalc = OpenGL style ---\n");
        std::cout << "cV_new " << cV_new << std::endl;

        /////////////////////////////////////////////////////
        // RowMajorData & ColMajorCalc = Opencv, numpy style
        /////////////////////////////////////////////////////
        rS << 1.f, 0.f, 0.f, 0.f,
            0.f, 2.f, 0.f, 0.f,
            0.f, 0.f, 3.f, 0.f,
            0.f, 0.f, 0.f, 1.f;
        rR << cosf(M_PI_4), -sinf(M_PI_4), 0.f, 0.f,
            sinf(M_PI_4), cosf(M_PI_4), 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f;
        rT << 0.f, 0.f, 0.f, 0.5f,
            0.f, 0.f, 0.f, 1.f,
            0.f, 0.f, 0.f, 1.5f,
            0.f, 0.f, 0.f, 1.0f;

        rM = rT * rR * rS;
        // rV_new = rM * rV; // (4,4) @ (1,4) Runtime Error!
        rV_new = rM * rV.transpose(); // (4,4) @ (1,4)^T = (4,1) -> (1,4) OK

        std::printf("--- RowMajorData & ColMajorCalc = OpenCV, numpy style ---\n");
        std::cout << "rV_new " << rV_new << std::endl;

        /////////////////////////////////////////////////////
        // ColMajorData & RowMajorCalc = ??? style
        /////////////////////////////////////////////////////
        cS << 1.f, 0.f, 0.f, 0.f,
            0.f, 2.f, 0.f, 0.f,
            0.f, 0.f, 3.f, 0.f,
            0.f, 0.f, 0.f, 1.f;
        cR << cosf(M_PI_4), sinf(M_PI_4), 0.f, 0.f,
            -sinf(M_PI_4), cosf(M_PI_4), 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f;
        cT << 0.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 0.f, 0.f,
            0.5f, 1.0f, 1.5f, 1.0f;

        cM = cS * cR * cT;
        // cV_new = cV * cM; // (4,1) @ (4,4) Runtime Error!
        cV_new = cV.transpose() * cM; // (4,1)^T @ (4,4) = (1,4) -> (4,1) OK

        std::printf("--- ColMajorData & RowMajorCalc = ??? style ---\n");
        std::cout << "cV_new " << cV_new << std::endl;

    
        /////////////////////////////////////////////
        // (1,4)ベクトルに(4,1)ベクトルを代入可能(逆もOK)
        /////////////////////////////////////////////
        ColMajorVector4f colVec; // (4,1)
        RowMajorVector4f rowVec; // (1,4)
        colVec << 1.f, 2.f, 3.f, 4.f;
        std::cout << "colVec " << colVec << std::endl;
        rowVec = colVec;
        std::cout << "rowVec " << rowVec << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
