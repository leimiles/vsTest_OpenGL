#include "users\shader.h"

// this is test shader
const char* shader::test_VertexShader = "#version 330\n"
"layout (location = 0) in vec3 pos_NDC;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(pos_NDC.x, pos_NDC.y, pos_NDC.z, 1.0);\n"
"}\n";

const char* shader::test_FragmentShader = "#version 330\n"
"out vec4 final_Color;\n"
"void main()\n"
"{\n"
"final_Color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";


shader::shader(/* args */)
{
}

shader::~shader()
{
}
