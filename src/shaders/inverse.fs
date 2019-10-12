#version 330 core

in vec3 customColor; 

out vec4 color; 

void main() {
    color = vec4(1 - customColor.x, 1 - customColor.y, 1 - customColor.z, 1.0);
}