/**
 * @file vector_ndim_type.cpp
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
 * @brief ベクトルの次元と型
 *
 * @return int
 */

int main(int, char **)
{
    try
    {
        // Vector[次元][型]
        // 次元：2,3,4,X(動的)
        // 型: d,f,i

        // よく使われる2次元、3次元、4次元ベクトルは用意されている
        Eigen::Vector2d a; // double
        Eigen::Vector2f b; // float
        Eigen::Vector2i c; // int

        Eigen::Vector3d d;
        Eigen::Vector3f e;
        Eigen::Vector3i f;

        Eigen::Vector4d g;
        Eigen::Vector4f h;
        Eigen::Vector4i i;

        // 複素数型も用意されている

        // 可変長次元ベクトル
        Eigen::VectorXd p;
        Eigen::VectorXf q;
        Eigen::VectorXi r;

        /**
         * @brief テンプレートパラメータ
         * https://qiita.com/yohm/items/a03006790dc1e54a87be
         *
         * 1. Matrix<typename Scalar, int RowsAtCompileTime, int ColsAtCompileTime>
         * 2. Matrix<double, Dynamic, Dynamic>
         * 3. typedef Matrix<double, Dynamic, Dynamic> MatrixXd;
         */

        /**
         * @brief 固定サイズと動的サイズ
         *
         * Eigenでは、コンパイル時にサイズ(=次元)が決まっているものを「固定サイズ」,
         * コンパイル時にサイズが分からないものを「動的サイズ」と呼ぶ。
         * 実行時にしか要素数がわからないものや16次元以上のものはDynamicを使うべき。
         */

        // usingを使ってエイリアスにする
        using Vector3i = Eigen::Matrix<int, 3, 1>;
        using Vector6f = Eigen::Matrix<float, 6, 1>;
        using Vector9d = Eigen::Matrix<double, 9, 1>;
        using VectorXi = Eigen::Matrix<int, Eigen::Dynamic, 1>;
        using VectorXf = Eigen::Matrix<float, Eigen::Dynamic, 1>;
        using VectorXd = Eigen::Matrix<double, Eigen::Dynamic, 1>;

        /**
         * @brief データの行優先と列優先
         * [m11, m12, m13]
         * [m21, m22, m23]
         * [m31, m32, m33]
         * と行列があるとき, メモリ配列として2パターンある
         * 1. [行優先] m11, m12, m13, m21, m22, m23, m31, m32, m33
         * 2. [列優先] m11, m21, m31, m12, m22, m32, m13, m23, m33
         * 行優先データ・・・C/C++, DirectX, OpenCV, numpy
         * 列優先データ・・・Fortran, Matrab(デフォルト), R, Eigen(デフォルト), OpenGL
         *
         * 主にデータのコピー時に問題になる
         * Eigenに関して
         * 行優先データ -> Matrix3i<int, 3, 3, Eigen::RowMajor>
         * 列優先データ -> Matrix3i<int, 3, 3, Eigen::ColMajor> (デフォルト)
         * で指定する.
         */
        using RowMajorMatrix3i = Eigen::Matrix<int, 3, 3, Eigen::RowMajor>;
        using ColMajorMatrix3i = Eigen::Matrix<int, 3, 3, Eigen::ColMajor>;
        using RowMajorVector3i = Eigen::Matrix<int, 1, 3, Eigen::RowMajor>;
        using ColMajorVector3i = Eigen::Matrix<int, 3, 1, Eigen::ColMajor>;

        

        /**
         * @brief 計算表記の行優先と列優先
         * 基本：一般数学は列優先表記, プログラム記述は列優先表記的
         * 列優先表記
         * v = [x
         *      y
         *      z]
         * M =
         * [s1r11, r12, r13, tx]
         * [r21, s2r22, r23, ty]
         * [r31, r32, s3r33, tz]
         * [0  , 0  , 0  , 1 ]
         * スケール→回転→並進
         * v_new = T@R@S * v = M * v
         * 
         * 行優先表記
         * v = [x y z]
         * M = 
         * [s1r11, r21, r31, 0]
         * [r12, s2r22, r32, 0]
         * [r13, r23, s3r33, 0]
         * [ tx,  ty,   tz,  1]
         * スケール→回転→並進
         * v_new = v * S@R@T = v * M
         * 
         * 列優先表記(数学表記)・・・OpenGL, OpenCV, numpy, Matlab, R
         * 行優先表記(プログラム的表記)・・・DirectX
         * 
         * 行列計算時に問題になる
         */

        /**
         * @brief データ順序と表記順序による効率
         * | データ順序 | 表記順序 | イメージの容易さ | 自然なプログラム記述 | モジュール例 |
         * | :-- | :-- | :-- | :-- | :-- |
         * | 列優先 | 列優先 | ◯ | × | Matlab(デフォルト), R, OpenGL |
         * | 列優先 | 行優先 | × | ◯ | プログラム記述を優先させたパターン |
         * | 行優先 | 列優先 | ◯ | × | OpenCV, numpy, (数学表記に従ったC/C++計算) |
         * | 行優先 | 行優先 | × | ◯ | DirectX, (プログラム記述を優先したC/C++計算)|
         *
         */
        
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}