/**
 * @file copy_to_std_container.cpp
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
 * @brief Eigenからstd::vectorへのマッピングは専用のアロケータを使うこと
 * @note Eigenは計算効率を高めるためにデータをアライメントを指定してメモリ上に連続に配列している.
 * アライメントはCPUのアーキテクチャ依存になるので, 注意が必要.
 * 
 * @note ただし, これはEigenの静的型変数に限られる.
 * Eigen::Vector4d -> 専用アロケータが必要.
 * Eigen::VectorXd -> 専用アロケータ必要ない.
 * 
 * @return int 
 */

int main(int, char**)
{
    try
    {
        // Eigenの静的ベクトル変数をstd::vectorにコピー
        {
            Eigen::Vector4d static_vec_4d_1;
            static_vec_4d_1 << 1.0, 2.0, 3.0, 4.0;
            Eigen::Vector4d static_vec_4d_2;
            static_vec_4d_2 << 2.0, 3.0, 4.0, 5.0;
            Eigen::Vector4d static_vec_4d_3;
            static_vec_4d_3 << 3.0, 4.0, 5.0, 6.0;
            
            std::vector<Eigen::Vector4d, Eigen::aligned_allocator< Eigen::Vector4d>> std_vec;

            // copy
            std_vec.emplace_back(static_vec_4d_1);
            std_vec.emplace_back(static_vec_4d_2);
            std_vec.emplace_back(static_vec_4d_3);

            for (auto &vec : std_vec)
            {
                std::cout << vec.transpose() << std::endl;
                std::cout << "---" << std::endl;
            }
        }

        std::cout << "-------------------------" << std::endl;

        // Eigenの静的ベクトル変数をstd::mapにコピ-
        {
            Eigen::Vector4d static_vec_4d_1;
            static_vec_4d_1 << 1.0, 2.0, 3.0, 4.0;
            Eigen::Vector4d static_vec_4d_2;
            static_vec_4d_2 << 2.0, 3.0, 4.0, 5.0;
            Eigen::Vector4d static_vec_4d_3;
            static_vec_4d_3 << 3.0, 4.0, 5.0, 6.0;

            using MapInt2Vec = std::map<int, Eigen::Vector4d, std::less<int>, Eigen::aligned_allocator<std::pair<const int, Eigen::Vector4d>>>;
            MapInt2Vec map_int_2_vec;

            // copy
            map_int_2_vec[0] = static_vec_4d_1;
            map_int_2_vec[1] = static_vec_4d_2;
            map_int_2_vec[2] = static_vec_4d_3;

            for (auto &pair : map_int_2_vec)
            {
                std::cout << pair.second.transpose() << std::endl;
                std::cout << "---" << std::endl;
            }
        }

        std::cout << "-------------------------" << std::endl;

        // Eigenの動的ベクトル変数をstd::vectorにコピー
        {
            // 動的型はコンストラクタで要素数を指定する
            Eigen::VectorXd dynamic_vec_d_1(4);
            dynamic_vec_d_1 << 0.0, 1.0, 2.0, 3.0;
            Eigen::VectorXd dynamic_vec_d_2(2);
            dynamic_vec_d_2 << 1.0, 2.0;
            Eigen::VectorXd dynamic_vec_d_3(3);
            dynamic_vec_d_3 << 3.0, 4.0, 5.0;
            std::cout << "dynamic_vec_d_1 " << dynamic_vec_d_1.transpose() << std::endl;
            std::cout << "dynamic_vec_2_d " << dynamic_vec_d_2.transpose() << std::endl;
            std::cout << "dynamic_vec_3_d " << dynamic_vec_d_3.transpose() << std::endl;

            using MapInt2DynamicVec = std::map<int, Eigen::VectorXd>;
            MapInt2DynamicVec mapToVec;

            mapToVec[0] = dynamic_vec_d_1;
            mapToVec[1] = dynamic_vec_d_2;
            mapToVec[2] = dynamic_vec_d_3;

            auto iter = mapToVec.begin();
            for (; iter != mapToVec.end(); ++iter)
            {
                std::cout << (*iter).second.transpose() << std::endl;
                std::cout << "---" << std::endl;
            }
        }

        std::cout << "-------------------------" << std::endl;

        // Eigenの静的ベクトル変数をstd::vector<std::vector>>にコピー
        {
            using StdCubeXxXx3f = std::vector<std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f>>>;
            StdCubeXxXx3f cube;
            constexpr int N = 5;
            cube.resize(N);
            for (auto& sh1 : cube) sh1.resize(N);

            Eigen::Vector3f vec;
            vec << 1.0, 2.0, 3.0;

            for (int y = 0; y < N; ++y)
            {
                for (int x = 0; x < N; ++x)
                {
                    cube.at(y).at(x) = vec; // copy
                }
            }

            for (int y = 0; y < N; ++y)
            {
                std::cout << "-----Height " << y << std::endl;
                for (int x = 0; x < N; ++x)
                {
                    std::cout << "---Width " << x << std::endl;
                    std::cout << "-Channel " << cube.at(y).at(x).transpose() << std::endl;
                }
            }
        }

        std::cout << "-------------------------" << std::endl;

        // Eigenの動的行列変数をstd::vector<std::vector>>にコピー
        {
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}