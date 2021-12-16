#pragma once
#ifndef CAM_H
#define CAM_H
#include "users/object.h"


class cam : protected object
{
private:
    float cam_Near_Plane;
    float cam_Far_Plane;
    // fov degree;
    float cam_Fov;
    float cam_Ratio;
    int cam_Width;
    int cam_Height;
    glm::vec3 cam_Target_Postion;
    glm::vec3 cam_Forward;
    glm::vec3 cam_Right;
    glm::vec3 cam_Up;
    glm::mat4 eye_Matrix;
    void set_Directions();
    void set_Forward();
    void set_Rightward();
    void set_Upward();
public:
    cam();
    ~cam();
    void set_Fov(float fov);
    void set_NearPlane(float nearPlane);
    void set_FarPlane(float farPlane);
    void set_Width(int width);
    void set_Height(int height);
    void set_Translate(float x, float y, float z);
    void set_Target(float x, float y, float z);
    void set_Rotate(float degrees, float x, float y, float z);
    glm::mat4 get_Matrix_PerspectiveProjection();
    glm::mat4 get_Matrix_WorldToView();
    glm::mat4 get_Matrix_ViewToWorld();
    glm::mat4 get_Matrix_LookingAt();
    void print_CamInfo();
};


#endif