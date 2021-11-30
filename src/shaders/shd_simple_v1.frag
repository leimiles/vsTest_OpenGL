#version 330

out vec4 final_Color;
in vec3 out_Color;
in vec2 out_Uv;

uniform sampler2D example1_Texture;
uniform sampler2D example2_Texture;

uniform float color_Intensity;

void main()
{
    vec4 vertex_Color = vec4(out_Color.r, out_Color.g, out_Color.b, 1.0f);
    vec4 example1_Color = texture(example1_Texture, out_Uv);
    vec4 example2_Color = texture(example2_Texture, out_Uv);
    final_Color = vec4(example1_Color.rgb * example2_Color.rgb, 1.0f) * color_Intensity;
}