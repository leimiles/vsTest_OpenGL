#version 330
out vec4 final_Color;
in vec3 color;
void main()
{
    final_Color = vec4(color.r, color.g, color.b, 1.0f);
}