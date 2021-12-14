#include "users/transform.h"

const glm::mat4 transform::mat_Identity = glm::mat4(1.0f);
const glm::vec3 transform::basis_X = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 transform::basis_Y = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 transform::basis_Z = glm::vec3(0.0f, 0.0f, 1.0f);

transform::transform()
{
    translate = glm::vec3(0.0f, 0.0f, 0.0f);
    rotate_degrees = 0.0f;
    rotate_Axis = glm::vec3(0.0f, 0.0f, 1.0f);
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
// set roate value, degrees, xyz
void transform::set_Rotate(float degrees, float x, float y, float z)
{
    if ((x + y + z) == 0.0f)
    {
        x = 1.0f;
        degrees = 0.0f;
    }
    rotate_degrees = degrees;
    rotate_Axis.x = x;
    rotate_Axis.y = y;
    rotate_Axis.z = z;
    rotate_Axis = glm::normalize(rotate_Axis);
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
    model_Matrix = transform::mat_Identity;
    model_Matrix = glm::translate(transform::mat_Identity, translate);
    model_Matrix = glm::rotate(model_Matrix, glm::radians(rotate_degrees), rotate_Axis);
    model_Matrix = glm::scale(model_Matrix, scale);
    return model_Matrix;
}

glm::mat4 transform::get_Matrix_WorldToLocal()
{
    model_Matrix = transform::mat_Identity;
    model_Matrix = glm::translate(transform::mat_Identity, translate);
    model_Matrix = glm::rotate(model_Matrix, glm::radians(rotate_degrees), rotate_Axis);
    model_Matrix = glm::scale(model_Matrix, scale);
    return glm::inverse(model_Matrix);
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
