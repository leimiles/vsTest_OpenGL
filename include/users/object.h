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
    virtual void set_Translate(float x, float y, float z) = 0;
    virtual void set_Rotate(float degrees, float x, float y, float z) = 0;
};

#endif