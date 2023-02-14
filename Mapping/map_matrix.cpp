/**
 * @file map_matrix.cpp
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
 * @brief 行列のデータ共有
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
        // Mapping Matrix
        {
            // from array[]
            const int N = 9;
            float array[N];
            for (int i = 0; i < N; ++i)
                array[i] = i;
            MatrixMap<float> matrixMap(array, 3, 3);
            std::cout << "matrixMap \n"
                      << matrixMap << std::endl;

            // from array[][]
            float arr2d[N][N];
            for (int y = 0; y < N; ++y)
            {
                for (int x = 0; x < N; ++x)
                {
                    if (y <= x)
                        arr2d[y][x] = y * x;
                    else
                        arr2d[y][x] = 0;
                }
            }
            Eigen::Map<Matrix<float>> matrixMap2d((float*)arr2d, N, N);
            std::cout << "matrixMap2d \n" << matrixMap2d << std::endl;

            // DefaultのColMajorの場合
            Eigen::Map<Eigen::MatrixXf> matrixMap2d_colmajor((float*)arr2d, N, N);
            std::cout << "matrixMap2d_colmajor \n"
                      << matrixMap2d_colmajor << std::endl; // ポインタのマッピングが転置になる
        }

        // Aligned & Strides Mapping Matrix
        {
            // specify strides
            // Eigen::InnerStride : 0軸目のストライド量(default 列方向)
            // Eigen::OuterStride : 1軸目のストライド量(default 行方向)

            // from array[]
            constexpr int N = 12;
            int array[N];
            for (int i = 0; i < N; ++i)
                array[i] = i;

            // OuterStride=3 (default)
            constexpr int AlignedByte = Eigen::AlignmentType::Unaligned; // defualt (byte align)
            Eigen::Map<Eigen::Matrix<int, 3, 4>, AlignedByte> M(array);
            std::cout << "M \n" << M << std::endl;

            // OuterStride=4
            Eigen::Map<Eigen::MatrixXi, AlignedByte, Eigen::OuterStride<>> stride_M(array, 3, 3, Eigen::OuterStride<>(4));
            std::cout << "stride_M \n" << stride_M << std::endl;

        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}