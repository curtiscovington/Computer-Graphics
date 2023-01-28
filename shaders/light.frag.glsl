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

vec3 checker(in float u, in float v)
{
  float checkSize = 8;
  float fmodResult = mod(floor(checkSize * u) + floor(checkSize * v), 2.0);
  float fin = max(sign(fmodResult), 0.0);
  return vec3(fin, fin, fin);
}

void main()
{
    const float gamma = 10.0;
    const float bloomBlur = 1.0;
    const float exposure = 1.0;

    vec3 bloomColor = vec3(1.0) - exp(-bloomBlur * exposure);
    
    // tone mapping
    // also gamma correct while we're at it       
    vec3 result = pow(bloomColor, vec3(1.0 / gamma));
    color = vec4(result, 1.0);
    color = vec4(1.0);
}
