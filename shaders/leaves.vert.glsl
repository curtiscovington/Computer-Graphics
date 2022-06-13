#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec3 a_normal;
layout(location = 3) in vec2 a_texCoord;

uniform mat4 u_viewProjection;
uniform mat4 u_modelMatrix;
uniform float u_time;
out vec3 v_position;
out vec4 v_color;
out vec2 v_texCoord;

void main()
{
    v_texCoord = a_texCoord;
    vec3 new_pos = a_position * (1.0 + 0.1 * sin(a_position.x+a_position.y+a_position.z+2.0*u_time));
    v_position = a_position;
    gl_Position = u_viewProjection * u_modelMatrix * vec4(new_pos, 1.0);
}