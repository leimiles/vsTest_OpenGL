#include "users/geometry.h"

geometry::geometry(unsigned int stride, unsigned int attributes_Size, float* attributes, unsigned int elements_Size, unsigned int* elements)
    : VERTEX_ATTRIBUTES_STRIDE(stride), VERTEX_ATTRIBUTES_SIZE(attributes_Size), VERTEX_ATTRIBUTES(attributes), VERTEX_ELEMENTS_SIZE(elements_Size), VERTEX_ELEMENTS(elements)
{
    geometry_Type = GL_TRIANGLES;
}

geometry::~geometry()
{
}

void geometry::set_Translate(float x, float y, float z)
{
    self_Transform.set_Translate(x, y, z);
}

void geometry::set_Rotate(float degrees, float x, float y, float z)
{
    self_Transform.set_Rotate(degrees, x, y, z);
}

void geometry::set_Scale(float x, float y, float z)
{
    self_Transform.set_Scale(x, y, z);
}

glm::mat4 geometry::get_Matrix_LocalToWorld()
{
    return self_Transform.get_Matrix_LocalToWorld();
}

glm::mat4 geometry::get_Matrix_WorldToLocal()
{
    return self_Transform.get_Matrix_WorldToLocal();
}
