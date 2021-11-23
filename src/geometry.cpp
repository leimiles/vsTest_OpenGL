#include "users/geometry.h"


// triangle vertices test, in order to skip vertex transform, we could use NDC coords directly
float geometry::triangle_Example[] = {
    -0.5f, -0.5f, 0.0f,     // position
    0.5f, -0.5f, 0.0f,      // position
    0.0f, 0.5f, 0.0f        // position
};

float geometry::triangle_Example_Colored[] = {
    -0.5f, -0.5f, 0.0f,     // position
    1.0f, 0.0f, 0.0f, 1.0f,         // color
    0.5f, -0.5f, 0.0f,      // position
    0.0f, 1.0f, 0.0f, 1.0f,         // color
    0.0f, 0.5f, 0.0f,       // position
    0.0f, 0.0f, 1.0f, 1.0f          // color
};

float geometry::rectangle_Example_Unique[] = {
    0.5f, 0.5f, 0.0f,       // top right
    0.5f, -0.5f, 0.0f,      // bottom right
    -0.5f, -0.5f, 0.0f,     // bottom left
    -0.5f, 0.5f, 0.0f       // top left
};

// not clock-wise ???
float geometry::rectangle_Example_Indices[] = {
    // 1st triangle
    0, 1, 3,
    // 2nd triangle
    1, 2, 3
};

geometry::geometry(/* args */)
{
}

geometry::~geometry()
{
}