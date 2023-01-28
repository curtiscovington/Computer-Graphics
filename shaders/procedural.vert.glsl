#version 410 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec3 a_normal;
layout(location = 3) in vec2 a_texCoord;

uniform mat4 u_viewProjection;
uniform mat4 u_modelMatrix;

out vec3 v_color;
out vec3 v_normal;
out vec2 v_texCoord;


out DATA
{
    vec2 texCoord;
    vec3 normal;
} data_out;

void main()
{
    gl_Position = u_modelMatrix * vec4(a_position, 1.0f);
    v_color = (vec3(gl_Position / gl_Position.w) + 1.0) / 2.0;

    v_texCoord = a_texCoord;
    v_normal = a_normal;

    data_out.texCoord = a_texCoord;
    data_out.normal = a_normal;
}