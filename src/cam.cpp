#include "users/cam.h"

cam::cam()
{
    // self member
    cam_near_Plane = 1.0f;
    cam_far_Plane = 100.0f;
    cam_fov = 45.0f;
    cam_width = 640;
    cam_height = 480;
    cam_ratio = (float)cam_width / (float)cam_height;  // 1.333

}

cam::~cam()
{
}

glm::mat4 cam::get_Matrix_PerspectiveProjection()
{
    return glm::perspective(glm::radians(cam_fov), cam_ratio, cam_near_Plane, cam_far_Plane);
}

void cam::set_Fov(float fov)
{
    cam_ratio = fov;
}

void cam::set_NearPlane(float nearPlane)
{
    cam_near_Plane = nearPlane;
}

void cam::set_FarPlane(float farPlane)
{
    cam_far_Plane = farPlane;
}

void cam::set_Width(int width)
{
    cam_width = width;
    cam_height = (int)((float)width / cam_ratio);
}

void cam::set_Height(int height)
{
    cam_height = height;
    cam_width = (int)((float)height * cam_ratio);
}

void cam::print_CamInfo()
{
    std::cout << "Cam Info:" << std::endl;
    std::cout << "near and far plane:\t" << cam_near_Plane << " | " << cam_far_Plane << std::endl;
    std::cout << "fov and ratio:\t" << cam_fov << " | " << cam_ratio << std::endl;
    std::cout << "width and height:\t" << cam_width << " | " << cam_height << std::endl;
}
