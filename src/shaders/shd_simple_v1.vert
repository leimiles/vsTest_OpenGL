#version 330
layout (location = 0) in vec3 pos_NDC;
layout (location = 1) in vec3 vertex_Color;
out vec3 color;

void main() {
    color = vertex_Color;
    gl_Position = vec4(pos_NDC.x, pos_NDC.y, pos_NDC.z, 1.0);
}