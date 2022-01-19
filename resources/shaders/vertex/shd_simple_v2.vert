#version 330

layout (location = 0) in vec3 pos_Obj;
layout (location = 1) in vec3 normal_Obj;
layout (location = 2) in vec2 texcoords;

out vec2 out_Uv;

uniform mat4 mvp;

void main() {
    out_Uv = texcoords;
    gl_Position = mvp * vec4(pos_Obj, 1.0f);
}