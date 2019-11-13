#version 330 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 tex_coord;

out vec2 vs_out_tex_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec2 tex_offset;
uniform vec2 atlas_size;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    vs_out_tex_coord =
        vec2((tex_coord.x + tex_offset.x) / atlas_size.x,
             ((1.0 - tex_coord.y) + tex_offset.y) / atlas_size.y);
}
