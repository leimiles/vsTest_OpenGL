#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "./glm/glm.hpp"
#include "./glm/gtc/matrix_transform.hpp"
#include "./glm/gtc/type_ptr.hpp"
#include <iostream>

class transform
{
private:
    // world transform, default 0
    glm::vec3 translate;
    // radians value, default 0, auto convert
    glm::vec3 rotateRad;
    // scale value, default 1.0
    glm::vec3 scale;
public:
    transform();
    ~transform();
    static const glm::mat4 mat_Identity;
    static const glm::vec3 basis_X;
    static const glm::vec3 basis_Y;
    static const glm::vec3 basis_Z;
    static void print_glmVector(glm::vec4 vector);
    static void print_glmVector(glm::vec3 vector);
    static void print_glmVector(glm::vec2 vector);
    static void print_glmMatrix(glm::mat4 matrix);
    static void print_glmMatrix(glm::mat3 matrix);
    static void print_glmMatrix(glm::mat2 matrix);
    // w, x, y, z
    static void print_glmQuaternion(glm::quat quat);
    // set translate value, xyz
    void set_Translate(float x, float y, float z);
    // set roate value, degrees, xyz
    void set_Rotate(float x, float y, float z);
    // set scale value 
    void set_Scale(float x, float y, float z);

};

#endif