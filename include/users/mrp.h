#pragma once
#include <glad/glad.h>
#include <users/geometry.h>
#include <users/shader.h>

// this is the render pipeline
class mrp
{
private:
public:
    mrp(/* args */);
    ~mrp();
    void clear_ColorBuffer();
    void draw_TestTriangle();
    void check_ShaderCompileInfo(unsigned int shaderID);
};
