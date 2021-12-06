#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "./glm/glm.hpp"
#include "./glm/gtc/matrix_transform.hpp"
#include "./glm/gtc/type_ptr.hpp"
#include <iostream>

class transform
{
private:
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
};

#endif