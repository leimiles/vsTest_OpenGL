#pragma once
#include <glad/glad.h>
#include <users/geometry.h>
#include <users/shader.h>

// this is the render pipeline
class mrp
{
private:
    static unsigned int current_VSO;        // vertex shader object
    static unsigned int current_FSO;        // fragment shader object
    static unsigned int current_Program;        // shader program object
    unsigned int current_VAO;       // vertex attribute object
public:
    mrp(/* args */);
    ~mrp();
    void test();
    void clear_ColorBuffer();
    void set_TestTriangleData();
    void set_TestShader(bool isChecked);
    void draw_TestTriangle();
    void check_ShaderCompileInfo(unsigned int shaderID);
    void check_ShaderLinkInfo(unsigned int shaderID);
};
