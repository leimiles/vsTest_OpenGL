#pragma once
#include <glad/glad.h>
#include <users/geometry.h>
#include <users/shader.h>

// this is the render pipeline
class mrp
{
private:
    static unsigned int current_VSO;
    static unsigned int current_FSO;
    static unsigned int current_Program;
    unsigned int current_VAO;
public:
    mrp(/* args */);
    ~mrp();
    void test();
    void clear_ColorBuffer();
    void set_TestTriangleData();
    void set_TestTriangleShader(bool isChecked);
    void draw_TestTriangle();
    void check_ShaderCompileInfo(unsigned int shaderID);
    void check_ShaderLinkInfo(unsigned int shaderID);
};
