/**
 * @file geometry_eular_angle.cpp
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
 * @brief Eular Angle
 * Euler angles might be convenient to create rotation objects.
 * On the other hand, since there exist 24 different conventions,
 * they are pretty confusing to use. This example shows how to
 * create a rotation matrix according to the 2-1-2 convention.
 *
 */

template <typename T>
T DegreeToRadian(T theta)
{
    return (T)(M_PI * theta / 180.0);
}

template <typename T>
T RadianToDegree(T radian)
{
    return (T)(180.0 * radian / M_PI);
}

int main(int, char**)
{
    std::cout << "[Let's check eular angle]" << std::endl;
    try
    {
        // オイラー角(α,β,γ)から回転行列を作る
        {
            // e.g ZYZ オイラー (内因性or外因性は定義による)
            float angle1 = DegreeToRadian(60.f);
            float angle2 = DegreeToRadian(30.f);
            float angle3 = DegreeToRadian(45.f);
            Eigen::Matrix3f rotFromEuler;
            rotFromEuler = Eigen::AngleAxisf(angle1, Eigen::Vector3f::UnitZ()) * Eigen::AngleAxisf(angle2, Eigen::Vector3f::UnitY()) * Eigen::AngleAxisf(angle3, Eigen::Vector3f::UnitZ());

            std::cout << "ZYZ Eular = (" << angle1 << "," << angle2 << "," << angle3 << ")" << std::endl;
            std::cout << "ZYZ Eular Rot = \n"
                      << rotFromEuler << std::endl;
        }

        std::cout << "--------------------" << std::endl;

        // ある回転行列からX軸(0), Y軸(1), Z軸(2) から3つを選んでオイラー角を求める
        {
            float theta = 60.f;
            Eigen::Vector3f angle_axis(1, 1, 1);
            angle_axis.normalize(); // (1/√3, 1/√3, 1/√3) θ=60
            Eigen::AngleAxisf angle_vector(DegreeToRadian(theta), angle_axis);
            Eigen::Affine3f rot3d;
            rot3d = angle_vector.toRotationMatrix();
            std::cout << "Rotation = \n"
                      << rot3d.matrix() << std::endl;

            Eigen::Vector3f ea = rot3d.linear().eulerAngles(2, 0, 2);
            float ea1 = RadianToDegree(ea[0]);
            float ea2 = RadianToDegree(ea[1]);
            float ea3 = RadianToDegree(ea[2]);

            std::printf("ZYZ Euler (%f,%f,%f)\n", ea1, ea2, ea3);

            // mat == AngleAxisf(ea[0], Vector3f::UnitZ()) 
            //      * AngleAxisf(ea[1], Vector3f::UnitX()) 
            //      * AngleAxisf(ea[2], Vector3f::UnitZ());
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}