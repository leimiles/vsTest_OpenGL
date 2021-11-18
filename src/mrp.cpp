#include "users/mrp.h"

mrp::mrp(/* args */)
{
}

mrp::~mrp()
{
}



// set(clear) color buffer with red
void mrp::clearColorBuffer()
{
    // set color buffer value
    glClearColor(0.2f, 0.6f, 0.6f, 1.0f);
    // clear color buffer with the set of clear color
    glClear(GL_COLOR_BUFFER_BIT);
    //std::cout << sizeof(vertices) << std::endl;
    //float* vertices;
    get_ExampleTriangle();
}