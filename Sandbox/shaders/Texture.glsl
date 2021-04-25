#type vertex
#version 330 core
#extension GL_ARB_separate_shader_objects: enable

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec2 a_texCoord;

uniform mat4 u_vp;
uniform mat4 u_transform;

out vec2 v_texCoord;
out vec2 v_screenPos;

void main() {
    v_texCoord = a_texCoord;
    gl_Position = u_vp * u_transform * vec4(a_pos, 1.0);
    v_screenPos = gl_Position.xy;
}

#type fragment
#version 330 core

uniform vec4 u_color;
uniform sampler2D u_texture;

layout(location = 0) out vec4 color;

in vec2 v_texCoord;
in vec2 v_screenPos;

void main() {
    float dist = 1.0f - distance(v_screenPos * 0.8f, vec2(0.0f));
    dist = clamp(dist, 0.0f, 1.0f);
    dist = sqrt(dist);
    color = texture(u_texture, v_texCoord) * u_color * dist;
}