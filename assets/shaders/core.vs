#version 330 core

layout(location = 0)in vec3 position; 
layout(location = 1)in vec3 color; 
layout(location = 2)in vec2 tex_coord; 

out vec3 vs_out_color; 
out vec2 vs_out_tex_coord; 

void main() {
    gl_Position = vec4(position, 1.0);
    vs_out_color = color;
    vs_out_tex_coord = vec2(tex_coord.x, 1.0 - tex_coord.y);
}
