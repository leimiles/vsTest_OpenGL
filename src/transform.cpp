#include "users/transform.h"

const glm::mat4 transform::mat_Identity = glm::mat4(1.0f);
const glm::vec3 transform::basis_X = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 transform::basis_Y = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 transform::basis_Z = glm::vec3(0.0f, 0.0f, 1.0f);

transform::transform()
{
    translate = glm::vec3(0.0f, 0.0f, 0.0f);
    rotateRad = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

transform::~transform()
{
}

void transform::set_Translate(float x, float y, float z)
{
    translate.x = x;
    translate.y = y;
    translate.z = z;
}

glm::vec3 transform::get_Translate()
{
    return translate;
}

// set roate value, degrees, xyz
void transform::set_Rotate(float x, float y, float z)
{
    rotateRad.x = glm::radians(x);
    rotateRad.y = glm::radians(y);
    rotateRad.z = glm::radians(z);
}
// set scale value 
void transform::set_Scale(float x, float y, float z)
{
    scale.x = x;
    scale.y = y;
    scale.z = z;
}

glm::mat4 transform::get_Matrix_LocalToWorld()
{
    glm::mat4 mat = glm::translate(transform::mat_Identity, translate);
    return glm::scale(mat, scale);
}

glm::mat4 transform::get_Matrix_WorldToLocal()
{
    glm::mat4 mat = glm::translate(transform::mat_Identity, translate);
    mat = glm::scale(mat, scale);
    return glm::inverse(mat);
}

void transform::print_glmVector(glm::vec4 vector)
{
    std::cout << vector.x << "\t" << vector.y << "\t" << vector.z << "\t" << vector.w << std::endl;
}

void transform::print_glmVector(glm::vec3 vector)
{
    std::cout << vector.x << "\t" << vector.y << "\t" << vector.z << std::endl;
}

void transform::print_glmVector(glm::vec2 vector)
{
    std::cout << vector.x << "\t" << vector.y << std::endl;
}

void transform::print_glmMatrix(glm::mat4 matrix)
{
    matrix = glm::transpose(matrix);
    std::cout << matrix[0][0] << "\t" << matrix[0][1] << "\t" << matrix[0][2] << "\t" << matrix[0][3] << std::endl;
    std::cout << matrix[1][0] << "\t" << matrix[1][1] << "\t" << matrix[1][2] << "\t" << matrix[1][3] << std::endl;
    std::cout << matrix[2][0] << "\t" << matrix[2][1] << "\t" << matrix[2][2] << "\t" << matrix[2][3] << std::endl;
    std::cout << matrix[3][0] << "\t" << matrix[3][1] << "\t" << matrix[3][2] << "\t" << matrix[3][3] << std::endl;
}

void transform::print_glmMatrix(glm::mat3 matrix)
{
    matrix = glm::transpose(matrix);
    std::cout << matrix[0][0] << "\t" << matrix[0][1] << "\t" << matrix[0][2] << std::endl;
    std::cout << matrix[1][0] << "\t" << matrix[1][1] << "\t" << matrix[1][2] << std::endl;
    std::cout << matrix[2][0] << "\t" << matrix[2][1] << "\t" << matrix[2][2] << std::endl;
}

void transform::print_glmMatrix(glm::mat2 matrix)
{
    matrix = glm::transpose(matrix);
    std::cout << matrix[0][0] << "\t" << matrix[0][1] << std::endl;
    std::cout << matrix[1][0] << "\t" << matrix[1][1] << std::endl;
}

void transform::print_glmQuaternion(glm::quat quat)
{
    std::cout << quat.w << "\t" << quat.x << "\t" << quat.y << "\t" << quat.z << std::endl;
}
