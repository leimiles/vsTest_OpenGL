#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "./glm/glm.hpp"
#include "./glm/gtc/matrix_transform.hpp"
#include "./glm/gtc/type_ptr.hpp"
#include <iostream>

class transform
{
private:
    static glm::mat4 mat_Identify;
public:
    transform();
    ~transform();
    static glm::vec4 object_ToWorld_Position(glm::vec3 translate_World, glm::vec3 position_Object);
    static void print_glmVector(glm::vec4 vector);
    static void print_glmVector(glm::vec3 vector);
    static void print_glmVector(glm::vec2 vector);
    static void print_glmMatrix(glm::mat4 matrix);
    static void print_glmMatrix(glm::mat3 matrix);
    static void print_glmMatrix(glm::mat2 matrix);
};

#endif