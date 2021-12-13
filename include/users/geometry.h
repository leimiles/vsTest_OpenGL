#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "glad/glad.h"
#include <array>
#include <iostream>

class geometry
{
private:
public:
    const unsigned int VERTEX_ATTRIBUTES_SIZE;
    const unsigned int VERTE_ELEMENTS_SIZE;
    const float* VERTEX_ATTRIBUTES;
    const unsigned int* VERTEX_ELEMENTS;
    float* attribute_Data;
    GLenum geometry_Type;
    geometry(unsigned int attributes_Size, float* attributes, unsigned int elements_Size = 0, unsigned int* elements = nullptr);
    ~geometry();
};

#endif