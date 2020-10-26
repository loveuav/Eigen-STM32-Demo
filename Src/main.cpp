#include "Eigen"
#include "board.hpp"

int main(void)
{
    Board board;
    board.Init();

    // quaternion
    Eigen::Quaternionf q = Eigen::Quaternionf(1, 0, 0, 0); // (w,x,y,z)
    // rotation matrix
    Eigen::Matrix3f rotation_matrix3f = Eigen::Matrix3f::Identity();
    // euler angle
    Eigen::Vector3f euler_angles(0, 0, 45);

    // rotation matrix to quaternion
    q = Eigen::Quaternionf(rotation_matrix3f);
    // quaternion to rotation matrix
    rotation_matrix3f = q.matrix();
    // rotation matrix to euler angle
    euler_angles = rotation_matrix3f.eulerAngles(2, 1, 0);
    // quaternion to euler angle
    euler_angles = q.matrix().eulerAngles(2, 1, 0);

    // some basic example
    Eigen::Vector3f v = Eigen::Vector3f::Zero();
    Eigen::Vector3f v1(0, 0, 1);
    Eigen::Vector3f v2 = Eigen::Vector3f::Random();;
    Eigen::Matrix<float, 3, 3> m = Eigen::Matrix3f::Identity(); 

    m << 1, 0, 3,
        0, 2, 0,
        5, 0, 1;
    v = m.inverse() * v1 + v2.cross(v1); 

    while (1)
    {
        board.LED_Toggle();
        HAL_Delay(500);
    }

    return 0;
}
