#version 330 core

in vec3 customColor; 

out vec4 color; 

void main() {
    color = vec4(customColor.x, customColor.y, customColor.z, 1.0);
}