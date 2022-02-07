#version 330

out vec4 final_Color;
in vec2 out_Uv;

uniform sampler2D example1_Texture;
uniform sampler2D example2_Texture;
uniform sampler2D example3_Texture;

uniform float time;

void main()
{
    vec4 example1_Color = texture(example1_Texture, out_Uv);
    vec4 example2_Color = texture(example2_Texture, out_Uv);
    vec4 example3_Color = texture(example3_Texture, out_Uv);
    final_Color = vec4(1.0, 0.0, 0.0, 1.0);
}