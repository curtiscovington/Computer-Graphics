#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec3 a_normal;
layout(location = 3) in vec2 a_texCoord;

uniform mat4 u_viewProjection;
uniform mat4 u_modelMatrix;

out vec3 v_position;
out vec4 v_color;
out vec2 v_texCoord;

void main()
{
    v_texCoord = a_texCoord;
    v_position = a_position;
    gl_Position = u_viewProjection * u_modelMatrix * vec4(a_position, 1.0);
}