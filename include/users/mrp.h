#pragma once
#include <glad/glad.h>
#include <users/geometry.h>

// this is the render pipeline
class mrp
{
private:
public:
    mrp(/* args */);
    ~mrp();
    void clear_ColorBuffer();
    void draw_TestTriangle();
};
