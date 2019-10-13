#version 330 core

in vec3 color; 
in vec2 vs_out_tex_coord; 

out vec4 out_color; 

uniform sampler2D texture1; 

void main() {
    vec4 base_color = texture(texture1, vs_out_tex_coord);
    out_color = vec4(1.0 - base_color.x, 1.0 - base_color.y, 1.0 - base_color.z, base_color.w);
}