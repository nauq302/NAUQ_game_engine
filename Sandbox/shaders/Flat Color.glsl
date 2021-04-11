#type vertex
#version 330 core
#extension GL_ARB_separate_shader_objects: enable

layout(location = 0) in vec3 a_pos;

uniform mat4 u_vp;
uniform mat4 u_transform;

void main() {
    gl_Position = u_vp * u_transform * vec4(a_pos, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_color;

void main() {
    color = u_color;
}