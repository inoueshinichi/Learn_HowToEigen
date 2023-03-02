/**
 * @file geometry_cross.cpp
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
 * @brief 外積計算
 * @note (x,y,z,1), (other.x,other.y,other,z,1)の外積計算. *this.cross3(other); 式: axb
 * @note 複素数のn次元ベクトルの外積 *this.cross(other); 式: (a+ib)×(c+id)=(a×c−b×d)−i(a×d−b×c)
 *
 *
 */

int main(int, char**)
{
    try
    {
        // 外積は4次元Vectorのみ対応.
        Eigen::Vector4f a; a << 1.0f, 2.0f, 3.0f, 1.0f;
        Eigen::Vector4f b; b << 2.0f, 3.0f, 4.0f, 1.0f;
        Eigen::Vector4f cross_ab;
        cross_ab = a.cross3(b);
        std::cout << "cross_ab = \n" << cross_ab << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}