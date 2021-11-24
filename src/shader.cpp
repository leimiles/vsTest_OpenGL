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
"uniform vec4 myColor;"
"void main()\n"
"{\n"
"final_Color = vec4(1.0f, myColor.g, 0.2f, 1.0f);\n"
"}\n";

const char* shader::test_VertexShader2 = "#version 330\n"
"layout (location = 0) in vec3 pos_NDC;\n"
"layout (location = 1) in vec4 color;\n"
"out vec4 vertex_Color;\n"
"void main()\n"
"{\n"
"vertex_Color = color;\n"
"gl_Position = vec4(pos_NDC.x, pos_NDC.y, pos_NDC.z, 1.0);\n"
"}\n";

const char* shader::test_FragmentShader2 = "#version 330\n"
"out vec4 final_Color;\n"
"in vec4 vertex_Color;\n"
"void main()\n"
"{\n"
"final_Color = vec4(vertex_Color.r, vertex_Color.g, vertex_Color.b, vertex_Color.a);\n"
"}\n";




shader::shader(/* args */)
{
}

shader::~shader()
{
}
