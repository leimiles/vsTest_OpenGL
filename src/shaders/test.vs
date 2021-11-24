#version 330
layout (location = 0) in vec3 pos_NDC;

void main() {
    gl_Position = vec4(pos_NDC.x, pos_NDC.y, pos_NDC.z, 1.0);
}