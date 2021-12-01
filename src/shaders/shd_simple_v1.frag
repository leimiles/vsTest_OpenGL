#version 330

out vec4 final_Color;
in vec3 out_Color;
in vec2 out_Uv;

uniform sampler2D example1_Texture;
uniform sampler2D example2_Texture;
uniform sampler2D example3_Texture;
uniform sampler2D example4_Texture;


void main()
{
    final_Color = vec4(out_Color.r, out_Color.g, out_Color.b, 1.0f);
    //final_Color.rgb *= texture(example1_Texture, out_Uv).rgb;
    final_Color.rgb *= texture(example1_Texture, out_Uv).rgb;
    final_Color.rgb *= texture(example2_Texture, out_Uv).rgb;
}