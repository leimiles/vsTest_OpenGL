#include "users/geometry.h"

float geometry::quad_Example[] = {
    0.5f, 0.5f, 0.0f,       // top right
    1.0f, 1.0f, 0.0f,       // color
    0.5f, -0.5f, 0.0f,      // bottom right
    1.0f, 0.0f, 0.0f,       // color
    -0.5f, -0.5f, 0.0f,     // bottom left
    0.0f, 0.0f, 0.0f,       // color
    -0.5f, 0.5f, 0.0f,      // top left
    0.0f, 1.0f, 0.0f        // color
};

// not clock-wise ???
unsigned int geometry::quad_Example_Indices[] = {
    0, 1, 3,    // 1st triangle
    1, 2, 3     // 2nd triangle
};

geometry::geometry(/* args */)
{
}

geometry::~geometry()
{
}