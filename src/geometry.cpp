#include "users/geometry.h"

geometry::geometry(unsigned int stride, unsigned int attributes_Size, float* attributes, unsigned int elements_Size, unsigned int* elements)
    : VERTEX_ATTRIBUTES_STRIDE(stride), VERTEX_ATTRIBUTES_SIZE(attributes_Size), VERTEX_ATTRIBUTES(attributes), VERTEX_ELEMENTS_SIZE(elements_Size), VERTEX_ELEMENTS(elements)
{
    geometry_Type = GL_TRIANGLES;
}

geometry::~geometry()
{
}
