#include "users/geometry.h"


// triangle vertices test, in order to skip vertex transform, we could use NDC coords directly
float geometry::triangle_Example[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};

geometry::geometry(/* args */)
{
}

geometry::~geometry()
{
}