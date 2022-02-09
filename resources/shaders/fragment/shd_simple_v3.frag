#version 330
struct surface
{
    sampler2D texture02;
    sampler2D texture03;
};

out vec4 final_Color;
in vec2 out_Uv;

uniform surface surf;

uniform float time;

void main()
{
    vec4 texture02_Color = texture(surf.texture02, out_Uv * 5.0);
    vec4 texture03_Color = texture(surf.texture03, out_Uv * 5.0);
    final_Color = texture02_Color;
}