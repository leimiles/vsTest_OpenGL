#pragma once
#ifndef OBJECT_H
#define OBJECT_H
#include "users/transform.h"


class object
{
protected:
    transform self_Transform;
public:
    object();
    ~object();
    void set_Translate(float x, float y, float z);
    void set_Rotate(float degrees, float x, float y, float z);
    void set_Scale(float x, float y, float z);
    glm::mat4 get_Matrix_LocalToWorld() const;
    glm::mat4 get_Matrix_WorldToLocal() const;
};

#endif