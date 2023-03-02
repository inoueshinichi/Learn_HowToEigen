/**
 * @file geo_rotation.cpp
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
 * @brief 3次元変換(回転, スケール, 並進, アフィン)
 * 
 * @tparam T 
 * @param theta 
 * @return T 
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
    try
    {
        // 2D
        {
            std::srand(2023); // fix seed
            Eigen::Vector2f v;
            v = Eigen::Vector2f::Random();
            std::cout << "v = \n" << v << std::endl;

            // 2D回転
            {
                // 回転行列
                float theta = 60.f;
                Eigen::Rotation2Df rot(DegreeToRadian(theta));
                std::cout << "2D Rot matrix = \n" << rot.matrix() << std::endl; // 列優先表現
                std::cout << "2D Rotated v = \n" << rot.matrix() * v << std::endl;
            }
        }

        std::cout << "------------" << std::endl;

        // 3D
        {
            std::cout << "[Let's check rotation of 3D]" << std::endl;
            {
                float theta = 60.f;
                Eigen::Vector3f zup = Eigen::Vector3f::UnitZ();
                zup.normalize();
                std::cout << "Angle Axis Vector = \n" << zup << std::endl;

                // 回転ベクトル(単位ベクトル+回転角)
                Eigen::AngleAxisf ang_vec(DegreeToRadian(theta), zup);

                std::cout << "Angle Axis = \n" << ang_vec.axis() << std::endl;
                std::cout << "Angle = " << ang_vec.angle() << std::endl;

                // 回転ベクトル -> 回転行列
                Eigen::Matrix3f rot_mat;
                rot_mat = ang_vec.toRotationMatrix();
                std::cout << "Rotation matrix = \n" << rot_mat << std::endl;

                // 回転行列 -> 回転ベクトル
                Eigen::AngleAxisf ret_ang_vec;
                ret_ang_vec.fromRotationMatrix(rot_mat);
                std::cout << "Ret Angle Axis = \n" << ret_ang_vec.axis() << std::endl;
                std::cout << "Ret Angle = " << RadianToDegree(ret_ang_vec.angle()) << std::endl;

                // 回転ベクトル -> クォータニオン
                Eigen::Quaternionf q(ang_vec); // 60°
                Eigen::Quaternionf p(ang_vec); // 60°
                // concatenate
                Eigen::Quaternionf pq(p * q); // 60° + 60°
                std::cout << "Coeffs of pq (Quaternion) = \n" << pq.coeffs() << std::endl;
                std::cout << "Vec of pq (Quaternion) = \n" << pq.vec() << std::endl;

                // クォータニオン -> 回転行列 -> 回転ベクトル
                Eigen::AngleAxisf con_ang_vec;
                Eigen::Matrix3f con_rot;
                con_rot = pq.toRotationMatrix();
                std::cout << "Rotation mat of pq = \n" << con_rot << std::endl;
                con_ang_vec.fromRotationMatrix(con_rot);
                std::cout << "Con Angle Axis = \n" << con_ang_vec.axis() << std::endl;
                std::cout << "Con Angle = " << RadianToDegree(con_ang_vec.angle()) << std::endl; // 120°

                // Slerp
                Eigen::Quaternionf slerped_q;
                float ratio = 0.5f; // f = 0.5f
                slerped_q = pq.slerp(ratio, q); // q * f + (1 - f) * pq
                Eigen::Matrix3f slerped_rot;
                slerped_rot = slerped_q.toRotationMatrix();
                std::cout << "Rotation mat of slerped_q between q and pq = \n" << slerped_rot << std::endl;
                Eigen::AngleAxisf slerped_av;
                slerped_av.fromRotationMatrix(slerped_rot);
                std::cout << "Slerped Angle Vector Axis = \n" << slerped_av.axis() << std::endl;
                std::cout << "Slerped Angle = " << RadianToDegree(slerped_av.angle()) << std::endl;
            }

            std::cout <<  "[Let's check scaling of 3D]" << std::endl;
            {
                Eigen::Matrix3f scale3d = Eigen::Scaling<float>(1.5, 1.5, 1.5);
                std::cout << "Scaling matrix = \n" << scale3d << std::endl;
            }

            std::cout << "[Let's check translation of 3D]" << std::endl;
            {
                Eigen::Affine3f affine3f;
                affine3f = Eigen::Translation3f(10, 20, 30);
                std::cout << "Translation matrix = \n" << affine3f.matrix() << std::endl;
            }

            std::cout << "[Let's check transform of 3D]" << std::endl;
            {
                // translation
                Eigen::Affine3f trans3d;
                trans3d = Eigen::Translation3f(10, 20, 30); // (10, 20, 30)
                std::cout << "Translation = \n" << trans3d.matrix() << std::endl;

                // rotation
                float theta = 60.f;
                Eigen::Vector3f angle_axis(1, 1, 1);
                angle_axis.normalize(); // (1/√3, 1/√3, 1/√3) θ=60
                Eigen::AngleAxisf angle_vector(DegreeToRadian(theta), angle_axis);
                Eigen::Affine3f rot3d;
                rot3d = angle_vector.toRotationMatrix();
                std::cout << "Rotation = \n" << rot3d.matrix() << std::endl;

                // scaling
                Eigen::Matrix3f scaling;
                scaling = Eigen::Scaling<float>(2.f, 2.f, 2.f); // (2,2,2)
                Eigen::Affine3f scale3d;
                scale3d = scaling;
                std::cout << "Scaling = \n" << scale3d.matrix() << std::endl;

                // Transform (EigenではVectorとPointの変数としての差異はない.)
                Eigen::Affine3f transform; // (3+1,3+1) = (4,4)行列
                transform = trans3d * rot3d * scale3d; // 列優先表現によるアフィン変換行列
                std::cout << "transform = trans3d * rot3d * scale3d = \n" << transform.matrix() << std::endl;
                Eigen::Vector4f start_vec(1.0, 0.0, 0.0, 1.0); // 変換前ベクトル
                Eigen::Vector4f end_vec; // 変換後ベクトル
                end_vec = transform * start_vec;
                std::cout << "start_vec = \n" << start_vec << std::endl;
                std::cout << "end_vec = \n" << end_vec << std::endl;

                // transform.linear()は回転行列+スケーリングの(3,3)部分だけを抜き出す
                std::cout << "transform.linear() = \n"
                          << transform.linear() << std::endl;

                std::cout << "inverse(trans3d * rot3d * scale3d) = \n" << transform.matrix().inverse() << std::endl;
            }

            

            std::cout << "[OpenGL compability]" << std::endl;
            {
               // OpenGL compatibility 3D glLoadMatrixf(t.data());

                /*
                 OpenGL compatibility 2D
                 Affine3f aux(Affine3f::Identity());
                 aux.linear().topLeftCorner<2,2>() = t.linear();
                 aux.translation().start<2>() = t.translation();
                 glLoadMatrixf(aux.data());
                */
            }
        }

        std::cout << "--------------------" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}