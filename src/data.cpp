#include "users/data.h"

float data::help_Quad_Attributes[] = {
    50.5f, 50.5f, 0.0f,       // top right
    0.0f, 0.0f, 1.0f,       // normal
    1.0f, 1.0f,             // uv
    50.5f, -50.5f, 0.0f,      // bottom right
    0.0f, 0.0f, 1.0f,       // normal
    1.0f, 0.0f,             // uv
    -50.5f, -50.5f, 0.0f,     // bottom left
    0.0f, 0.0f, 1.0f,       // normal
    0.0f, 0.0f,             // uv
    -50.5f, 50.5f, 0.0f,      // top left
    0.0f, 0.0f, 1.0f,       // normal
    0.0f, 1.0f              // uv
};

// not clock-wise ???
unsigned int data::help_Quad_Indices[] = {
    0, 1, 3,    // 1st triangle
    1, 2, 3     // 2nd triangle
};

// this is a cube
float data::cube_Example_Attributes[] = {
    // position and uv
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 data::some_Positions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

std::string data::shader_Chicken01_Vert =
"#version 330\n"
"layout (location = 0) in vec3 pos_Obj;\n"
"layout (location = 1) in vec3 normal_Obj;\n"
"layout (location = 2) in vec2 texcoords;\n"
"out vec2 out_UV;\n"
"uniform mat4 matrix_MVP;\n"
"uniform mat4 matrix_LocalToWorld;\n"
"uniform mat4 matrix_ViewToPerspectiveProjection;\n"
"uniform mat4 matrix_Eye;\n"
"void main() {\n"
"    out_UV = texcoords;\n"
"    gl_Position = matrix_MVP * vec4(pos_Obj, 1.0f);\n"
"}\n"
;

std::string data::shader_Chicken01_Frag =
"#version 330\n"
"struct surface\n"
"{\n"
"    sampler2D diffuse;\n"
"};\n"
"out vec4 final_Color;\n"
"in vec2 out_UV;\n"
"uniform surface surf;\n"
"uniform float time;\n"
"void main()\n"
"{\n"
"    vec4 diffuse_Color = texture(surf.diffuse, out_UV);\n"
"    final_Color = diffuse_Color;\n"
"}\n"
;

