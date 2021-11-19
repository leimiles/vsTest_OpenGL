#include "users/mrp.h"

mrp::mrp(/* args */)
{
}

mrp::~mrp()
{
}

// set(clear) color buffer with specified color
void mrp::clear_ColorBuffer()
{
    // set clear color  value
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // clear color buffer with the set of clear color
    glClear(GL_COLOR_BUFFER_BIT);
}

void mrp::draw_TestTriangle()
{
    std::cout << sizeof(geometry::triangle_Example) << std::endl;
}
