#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class transform
{
private:
    // world transform, default 0
    glm::vec3 translate;
    // rotate degrees
    float rotate_degrees;
    // rotate axis
    glm::vec3 rotate_Axis;
    // scale value, default 1.0
    glm::vec3 scale;
    // model matrix
    //glm::mat4 model_Matrix;
public:
    transform();
    ~transform();
    static const glm::mat4 mat_Identity;
    // the world uses left hand coordinate system
    static const glm::vec3 basis_X;
    static const glm::vec3 basis_Y;
    static const glm::vec3 basis_Z;
    static void print_glmVector(glm::vec4 vector);
    static void print_glmVector(glm::vec3 vector);
    static void print_glmVector(glm::vec2 vector);
    static void print_glmMatrix(glm::mat4 matrix);
    static void print_glmMatrix(glm::mat3 matrix);
    static void print_glmMatrix(glm::mat2 matrix);
    static void print_glmQuaternion(glm::quat quat);
    void set_Translate(float x, float y, float z);
    void set_Rotate(float degrees, float x, float y, float z);
    void set_Scale(float x, float y, float z);
    glm::vec3 get_Translate();
    glm::mat4 get_Matrix_LocalToWorld() const;
    glm::mat4 get_Matrix_WorldToLocal() const;
};

#endif