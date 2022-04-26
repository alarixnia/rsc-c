#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec4 colour;
layout (location = 2) in vec3 texture_position;

out vec4 vertex_colour;
out vec3 vertex_texture_position;

void main() {
    gl_Position = vec4(position, 0.0, 1.0);
    vertex_colour = colour;
    vertex_texture_position = texture_position;
}