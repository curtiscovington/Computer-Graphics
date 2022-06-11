#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec3 a_normal;

uniform mat4 u_viewProjection;
out vec3 v_position;
out vec4 v_color;

void main()
{
    v_position = a_position;
    v_color = a_color;

    gl_Position = u_viewProjection * vec4(a_position, 1.0);
}