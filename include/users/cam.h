#pragma once
#ifndef CAM_H
#define CAM_H
#include "users/object.h"


class cam : public object
{
private:
    float cam_near_Plane;
    float cam_far_Plane;
    // fov degree;
    float cam_fov;
    float cam_ratio;
    int cam_width;
    int cam_height;

public:
    cam(transform& trans);
    ~cam();
    void set_Fov(float fov);
    void set_NearPlane(float nearPlane);
    void set_FarPlane(float farPlane);
    void set_Width(int width);
    void set_Height(int height);
    glm::mat4 get_Matrix_PerspectiveProjection();
    void print_CamInfo();
};


#endif