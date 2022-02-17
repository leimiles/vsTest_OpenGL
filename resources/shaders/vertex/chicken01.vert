#version 330

layout (location = 0) in vec3 pos_Obj;
layout (location = 1) in vec3 normal_Obj;
layout (location = 2) in vec2 texcoords;

out vec2 out_UV;

uniform mat4 matrix_MVP;
uniform mat4 matrix_LocalToWorld;
uniform mat4 matrix_WorldToView;
uniform mat4 matrix_ViewToPerspectiveProjection;
uniform mat4 matrix_Eye;

void main() {
    out_UV = texcoords;
    gl_Position = matrix_MVP * vec4(pos_Obj, 1.0f);
}