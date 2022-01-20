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
    cam_Target_Postion = glm::vec3(0.0f);
    set_Translate(0.0f, 0.0f, 3.0f);
    eye_Matrix = get_Matrix_Eye();
}

cam::~cam()
{
}

void cam::set_Translate(float x, float y, float z)
{
    if (x == cam_Target_Postion.x && y == cam_Target_Postion.y && z == cam_Target_Postion.z)
    {
        z += 0.0001f;
    }
    self_Transform.set_Translate(x, y, z);
    set_Directions();
}

void cam::set_Scale(float x, float y, float z)
{
    // scale cam means nothing...
}

void cam::set_Target(float x, float y, float z)
{
    glm::vec3 position = self_Transform.get_Translate();
    if (x == position.x && y == position.y && z == position.z) {
        z += 0.0001f;
    }
    cam_Target_Postion.x = x;
    cam_Target_Postion.y = y;
    cam_Target_Postion.z = z;
    set_Directions();
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

// by target coordinates
glm::mat4 cam::get_Matrix_Eye()
{
    eye_Matrix = glm::lookAt(self_Transform.get_Translate(), cam_Target_Postion, transform::basis_Y);
    return eye_Matrix;
}

// imporoved to avoid vertical eye matrix bug
glm::mat4 cam::get_Matrix_Eye_Improved()
{

    glm::mat4 eye_Directions(1.0f);
    eye_Directions[0][0] = cam_Right.x;
    eye_Directions[0][1] = cam_Right.y;
    eye_Directions[0][2] = cam_Right.z;
    eye_Directions[1][0] = cam_Up.x;
    eye_Directions[1][1] = cam_Up.y;
    eye_Directions[1][2] = cam_Up.z;
    eye_Directions[2][0] = cam_Forward.x;
    eye_Directions[2][1] = cam_Forward.y;
    eye_Directions[2][2] = cam_Forward.z;

    glm::mat4 trans(1.0f);
    trans[0][3] = self_Transform.get_Translate().x * -1.0f;
    trans[1][3] = self_Transform.get_Translate().y * -1.0f;
    trans[2][3] = self_Transform.get_Translate().z * -1.0f;
    eye_Matrix = glm::transpose(trans * eye_Directions);

    return eye_Matrix;
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
        cam_Forward = glm::normalize(position - cam_Target_Postion);
    }
}

void cam::set_Rightward()
{

    if (cam_Forward == transform::basis_Y)
    {
        cam_Forward.z = 0.0001f;
        cam_Forward = glm::normalize(cam_Forward);
    }
    cam_Right = glm::normalize(glm::cross(transform::basis_Y, cam_Forward));

}

void cam::set_Upward()
{
    cam_Up = glm::normalize(glm::cross(cam_Forward, cam_Right));
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
    std::cout << "\tnear and far plane:\t" << cam_Near_Plane << " | " << cam_Far_Plane << std::endl;
    std::cout << "\tfov and ratio:     \t" << cam_Fov << " | " << cam_Ratio << std::endl;
    std::cout << "\twidth and height:  \t" << cam_Width << " | " << cam_Height << std::endl;
    std::cout << "\tcam forward:       \t" << cam_Forward.x << "\t" << cam_Forward.y << "\t" << cam_Forward.z << std::endl;
    std::cout << "\tcam right:         \t" << cam_Right.x << "\t" << cam_Right.y << "\t" << cam_Right.z << std::endl;
    std::cout << "\tcam up:            \t" << cam_Up.x << "\t" << cam_Up.y << "\t" << cam_Up.z << std::endl;
    std::cout << "eye_Matrix: (default)" << std::endl;
    transform::print_glmMatrix(get_Matrix_Eye());
    std::cout << " *********************************************** " << std::endl;
    std::cout << "eye_Matrix: (improved)" << std::endl;
    transform::print_glmMatrix(get_Matrix_Eye_Improved());
    std::cout << " *********************************************** " << std::endl;
}

void cam::set_SphericalSystem(float radius, float elevationAngle_Degrees, float turningAngle_Degrees)
{
    if (elevationAngle_Degrees > 179.9001f) {
        elevationAngle_Degrees = 179.9001f;
    }
    if (elevationAngle_Degrees < 0.1f) {
        elevationAngle_Degrees = 0.1f;
    }
    if (radius == 0.0f) {
        radius = 0.0001f;
    }
    float elevationAngle_Radians = glm::radians(elevationAngle_Degrees);
    float turningAngle_Radians = glm::radians(turningAngle_Degrees);
    float x = radius * sin(elevationAngle_Radians) * sin(turningAngle_Radians);
    float y = radius * cos(elevationAngle_Radians);
    float z = radius * sin(elevationAngle_Radians) * cos(turningAngle_Radians);
    //std::cout << elevationAngle_Radians << " | " << turningAngle_Radians << std::endl;
    //std::cout << "x: " << x << std::endl;
    //std::cout << "y: " << y << std::endl;
    //std::cout << "z: " << z << std::endl;
    set_Translate(x, y, z);
    set_Directions();
}

void cam::set_SphericalSystem_With_Target(float radius, float elevationAngle_Degrees, float turningAngle_Degrees)
{
    if (elevationAngle_Degrees > 179.9001f) {
        elevationAngle_Degrees = 179.9001f;
    }
    if (elevationAngle_Degrees < 0.1f) {
        elevationAngle_Degrees = 0.1f;
    }
    if (radius == 0.0f) {
        radius = 0.0001f;
    }
    float elevationAngle_Radians = glm::radians(elevationAngle_Degrees);
    float turningAngle_Radians = glm::radians(turningAngle_Degrees);
    float x = radius * sin(elevationAngle_Radians) * sin(turningAngle_Radians) - cam_Target_Postion.x;
    float y = radius * cos(elevationAngle_Radians) - cam_Target_Postion.y * (-1.0f);
    float z = radius * sin(elevationAngle_Radians) * cos(turningAngle_Radians) - cam_Target_Postion.z;
    //std::cout << elevationAngle_Radians << " | " << turningAngle_Radians << std::endl;
    //std::cout << "x: " << x << std::endl;
    //std::cout << "y: " << y << std::endl;
    //std::cout << "z: " << z << std::endl;
    set_Translate(x, y, z);
    set_Directions();
}
