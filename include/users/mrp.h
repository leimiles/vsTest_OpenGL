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
    unsigned int current_VBO;
public:
    mrp(/* args */);
    ~mrp();
    void test();
    void clear_ColorBuffer();
    void set_TestTriangleData();
    void set_TestTriangleData2();
    void set_TestShader(bool isChecked);
    void set_ShaderProgram(const char* vertex_Shader, const char* fragment_Shader, bool isChecked);
    void delete_Shaders();
    void draw_TestTriangle();
    void draw_TrianglesArray(unsigned int start_Index, unsigned int vertices_Count);
    void check_ShaderCompileInfo(unsigned int shaderID);
    void check_ShaderLinkInfo(unsigned int shaderID);
};
