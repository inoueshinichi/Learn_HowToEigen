/**
 * @file map_from_stl_vector.cpp
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
 * @brief ベクトルの
 *
 */
template <typename T>
using Matrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
template <typename T>
using RowVector = Eigen::Matrix<T, 1, Eigen::Dynamic>;
template <typename T>
using ColVector = Eigen::Matrix<T, Eigen::Dynamic, 1>;
template <typename T>
using MatrixMap = Eigen::Map<Matrix<T>>;
template <typename T>
using RowVectorMap = Eigen::Map<RowVector<T>>;
template <typename T>
using ColVectorMap = Eigen::Map<ColVector<T>>;
template <typename T>
using ConstMatrixMap = Eigen::Map<const Matrix<T>>;
template <typename T>
using ConstRowVectorMap = Eigen::Map<const RowVector<T>>;
template <typename T>
using ConstColVectorMap = Eigen::Map<const ColVector<T>>;

int main(int, char **)
{
    try
    {
        // Mapping Vector
        // 配列サイズがわかっている＆メモリが連続していることが共有条件
        {
            const int N = 24;
            const int M = 8;

            // from std::vector
            std::vector<float> std_vec(N);
            for (int i = 0; i < std_vec.size(); ++i)
                std_vec[i] = i;
            ConstRowVectorMap<float> std_rV(std_vec.data(), std_vec.size());
            std::cout << "std_rV " << std_rV << std::endl;
            std::cout << "std_rV(0) " << std_rV(0) << std::endl;

            // from std::array
            std::array<float, M> std_arr;
            for (int i = 0; i < std_arr.size(); ++i)
                std_arr[i] = 0;
            ConstColVectorMap<float> std_cV(std_arr.data(), std_arr.size());
            std::cout << "std_cV \n"
                      << std_cV << std::endl;

            // from int[]
            const int U = 5;
            int array[U] = {5, 4, 3, 2, 1};
            ConstRowVectorMap<int> arr_rV(array, U);
            std::cout << "arr_rV " << arr_rV << std::endl;

            // from pointer
            const int L = 10;
            float *pointer = new float[L];
            for (int i = 0; i < L; ++i)
                pointer[i] = i;
            RowVectorMap<float> p_rV(pointer, L);
            std::cout << "p_rV " << p_rV << std::endl;
            p_rV(0) = 100;
            std::cout << "modify p_rV " << p_rV << std::endl;
            delete[] pointer;

            // placement new演算子による再マッピング
            int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            Eigen::Map<Eigen::RowVectorXi> v(data, 4);
            std::cout << "The mapped vector v is: " << v << std::endl;
            new (&v) Eigen::Map<Eigen::RowVectorXi>(data + 4, 5);
            std::cout << "Now v is: " << v << std::endl;
        }

        // Aligned & Strides Mapping Vector
        {
            // specify strides
            // Eigen::InnerStride : 0軸目のストライド量(default 列方向)
            // Eigen::OuterStride : 1軸目のストライド量(default 行方向)

            const int K = 20;
            double *array = new double[K];
            for (int i = 0; i < K; ++i)
                array[i] = i;
            constexpr int AlignedByte = Eigen::AlignmentType::Unaligned; // defualt (byte align)
            Eigen::Map<Eigen::VectorXd, AlignedByte, Eigen::InnerStride<2>> stride_cVec(array, K / 2);
            std::cout << "stride_cVec " << stride_cVec << std::endl;
            delete[] array;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}