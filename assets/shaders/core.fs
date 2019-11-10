#version 330 core

in vec2 vs_out_tex_coord;

out vec4 out_color;

uniform sampler2D texture1;

void main()
{
    out_color = texture(texture1, vs_out_tex_coord);
}