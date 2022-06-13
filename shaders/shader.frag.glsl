#version 330 core
layout(location = 0) out vec4 color;

in vec3 v_position;
in vec4 v_color;
in vec2 v_texCoord;

uniform sampler2D u_gSampler;
void main()
{
    color = vec4(v_position * 0.5 + 0.5, 1.0);
    color = v_color;

    color = texture2D(u_gSampler, v_texCoord);
}