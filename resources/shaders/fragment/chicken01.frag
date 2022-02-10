#version 330
struct surface
{
    sampler2D diffuse;
};

out vec4 final_Color;
in vec2 out_UV;

uniform surface surf;

uniform float time;

void main()
{
    vec4 diffuse_Color = texture(surf.diffuse, out_UV);
    final_Color = diffuse_Color;
}