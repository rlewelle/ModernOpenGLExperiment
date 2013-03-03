#version 330 core

uniform mat4 transform;

in vec3 coord;
in vec2 tex;

out vec2 fTex;

void main(void) {
    gl_Position = transform * vec4(coord, 1.0);
    fTex = tex;
}