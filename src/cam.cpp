#include "users/cam.h"

cam::cam()
{
    // self member
    cam_Near_Plane = 1.0f;
    cam_Far_Plane = 100.0f;
    cam_Fov = 45.0f;
    cam_Width = 640;
    cam_Height = 480;
    cam_Ratio = (float)cam_Width / (float)cam_Height;  // 1.333
    cam_Target_Postion = transform::basis_Z * -1.0f;
    cam_Forward = transform::basis_Z * -1.0f;
    cam_Up = transform::basis_Y;
    cam_Right = transform::basis_X;
}

cam::~cam()
{
}

void cam::set_Translate(float x, float y, float z)
{
    self_Transform.set_Translate(x, y, z);
    set_Directions();
}

void cam::set_Target(float x, float y, float z)
{
    cam_Target_Postion.x = x;
    cam_Target_Postion.y = y;
    cam_Target_Postion.z = z;
    set_Directions();
}

void cam::set_Rotate(float degrees, float x, float y, float z)
{
    self_Transform.set_Rotate(degrees, x, y, z);
}

glm::mat4 cam::get_Matrix_PerspectiveProjection()
{
    return glm::perspective(glm::radians(cam_Fov), cam_Ratio, cam_Near_Plane, cam_Far_Plane);
}

glm::mat4 cam::get_Matrix_WorldToView()
{
    return self_Transform.get_Matrix_WorldToLocal();
}

glm::mat4 cam::get_Matrix_ViewToWorld()
{
    return self_Transform.get_Matrix_LocalToWorld();
}

// by world
glm::mat4 cam::get_Matrix_LookingAt()
{
    glm::mat4 lookingAt;
    lookingAt = glm::lookAt(self_Transform.get_Translate(), cam_Target_Postion, transform::basis_Y);
    return lookingAt;
}

void cam::set_Directions()
{
    set_Forward();
    set_Rightward();
    set_Upward();
}

// cam direction pointing at 0, 0, -1 by default
void cam::set_Forward()
{
    glm::vec3 position = self_Transform.get_Translate();
    if (cam_Target_Postion != position) {
        cam_Forward = glm::normalize(cam_Target_Postion - position);
    }
}

void cam::set_Rightward()
{
    cam_Right = glm::normalize(glm::cross(cam_Forward, transform::basis_Y));
}

void cam::set_Upward()
{
    cam_Up = glm::normalize(glm::cross(cam_Right, cam_Forward));
}

void cam::set_Fov(float fov)
{
    cam_Ratio = fov;
}

void cam::set_NearPlane(float nearPlane)
{
    cam_Near_Plane = nearPlane;
}

void cam::set_FarPlane(float farPlane)
{
    cam_Far_Plane = farPlane;
}

void cam::set_Width(int width)
{
    cam_Width = width;
    cam_Height = (int)((float)width / cam_Ratio);
}

void cam::set_Height(int height)
{
    cam_Height = height;
    cam_Width = (int)((float)height * cam_Ratio);
}

void cam::print_CamInfo()
{
    std::cout << "Cam Info:" << std::endl;
    std::cout << "near and far plane:\t" << cam_Near_Plane << " | " << cam_Far_Plane << std::endl;
    std::cout << "fov and ratio:\t" << cam_Fov << " | " << cam_Ratio << std::endl;
    std::cout << "width and height:\t" << cam_Width << " | " << cam_Height << std::endl;
}
