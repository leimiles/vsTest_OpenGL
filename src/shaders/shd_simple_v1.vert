#version 330

layout (location = 0) in vec3 vertex_pos_NDC;
layout (location = 1) in vec3 vertex_Color;
layout (location = 2) in vec2 vertex_Uv;

out vec3 out_Color;
out vec2 out_Uv;

uniform mat4 identified;

void main() {
    out_Color = vertex_Color;
    out_Uv = vertex_Uv;
    gl_Position = identified * vec4(vertex_pos_NDC, 1.0f);
}