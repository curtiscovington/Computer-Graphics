#version 410 core
layout(location = 0) out vec4 color;

in vec3 v_position;
in vec4 v_color;
in vec2 v_texCoord;
in vec3 v_normal;

in vec3 v_cameraPos;
in vec3 v_lightPos;

uniform sampler2D u_gSampler;
uniform sampler2D u_gSamplerNormalMap;
uniform mat4 u_modelMatrix;

uniform float u_time;

uniform mat4 u_viewProjection;

uniform bool u_useNormalMap;

uniform vec3 dim;

void main()
{
    color = vec4(gl_FragCoord.xyz/dim, 1.0);
}