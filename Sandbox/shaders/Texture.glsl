#type vertex
#version 330 core
#extension GL_ARB_separate_shader_objects: enable

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec2 a_texCoord;

uniform mat4 u_vp;
uniform mat4 u_transform;

out vec2 v_texCoord;

void main() {
    v_texCoord = a_texCoord;
    gl_Position = u_vp * u_transform * vec4(a_pos, 1.0);
}

#type fragment
#version 330 core


uniform sampler2D u_texture;

layout(location = 0) out vec4 color;

in vec2 v_texCoord;

void main() {
    color = texture(u_texture, v_texCoord * 10) * vec4(1.0, 0.0, 0.0, 1.0);
}