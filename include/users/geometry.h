#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <iostream>
#include <vector>
#include "glad/glad.h"
#include "users/object.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


struct vertexData
{
    glm::vec3 position_Obj;
    glm::vec3 normal_Obj;
    glm::vec2 texcoords;
};

class geometry : public object
{
private:
public:
    unsigned int VERTEX_ATTRIBUTES_SIZE;
    unsigned int VERTEX_ELEMENTS_SIZE;
    float* VERTEX_ATTRIBUTES;
    unsigned int* VERTEX_ELEMENTS;
    unsigned int VERTEX_ATTRIBUTES_STRIDE;
    GLenum geometry_Type;
    geometry(unsigned int stride, unsigned int attributes_Size, float* attributes, unsigned int elements_Size = 0, unsigned int* elements = nullptr);
    ~geometry();
};

#endif