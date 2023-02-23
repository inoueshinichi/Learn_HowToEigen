/**
 * @file packed_eigen_class.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-02-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <test_utils.hpp>

/**
 * @brief Eigenの静的変数をコンポジットしたクラス定義にはEIGEN_MAKE_ALIGNED_OPERATOR_NEWマクロを定義する
 *
 *
 * @return int
 */

class MyMatrix3f
{
private:
    Eigen::Matrix3f mMat;

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    MyMatrix3f() = default;
    ~MyMatrix3f() = default;
    MyMatrix3f(const MyMatrix3f &) = delete;
    MyMatrix3f &operator=(const MyMatrix3f &) = delete;
    MyMatrix3f(MyMatrix3f &&) = default;
    MyMatrix3f &operator=(MyMatrix3f &&) = default;

    void set(float mat[3][3])
    {
        mMat(0, 0) = mat[0][0];
        mMat(0, 1) = mat[0][1];
        mMat(0, 2) = mat[0][2];

        mMat(1, 0) = mat[1][0];
        mMat(1, 1) = mat[1][1];
        mMat(1, 2) = mat[1][2];

        mMat(2, 0) = mat[2][0];
        mMat(2, 1) = mat[2][1];
        mMat(2, 2) = mat[2][2];
    }

    Eigen::Matrix3f &get() { return mMat; }
};

int main(int, char **)
{
    try
    {
        MyMatrix3f myMat3f;

        float mat[3][3];
        mat[0][0] = 1.f * 1;
        mat[0][1] = 2.f * 1;
        mat[0][2] = 3.f * 1;
        mat[1][0] = 1.f * 2;
        mat[1][1] = 2.f * 2;
        mat[1][2] = 3.f * 2;
        mat[2][0] = 1.f * 3;
        mat[2][1] = 2.f * 3;
        mat[2][2] = 3.f * 3;

        myMat3f.set(mat);

        std::cout << "MyMatrix3f \n" << myMat3f.get() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}