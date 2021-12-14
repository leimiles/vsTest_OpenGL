#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "glad/glad.h"
#include "users/object.h"
#include <iostream>

class geometry : public object
{
private:
public:
    const unsigned int VERTEX_ATTRIBUTES_SIZE;
    const unsigned int VERTEX_ELEMENTS_SIZE;
    const float* VERTEX_ATTRIBUTES;
    const unsigned int* VERTEX_ELEMENTS;
    const unsigned int VERTEX_ATTRIBUTES_STRIDE;
    GLenum geometry_Type;
    geometry(unsigned int stride, unsigned int attributes_Size, float* attributes, unsigned int elements_Size = 0, unsigned int* elements = nullptr);
    ~geometry();
};

#endif