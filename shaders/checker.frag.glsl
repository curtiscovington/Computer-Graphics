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

float pointLight() {
    // get normals between -1 and 1 range
    vec3 normalMap = vec3(0.0f, 0.0f, 1.0f);
    
    // make a uniform
    vec4 u_lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    vec3 lightPos = vec3(0.0f, 0.0f, 0.0f);
    vec3 lightVec = lightPos - v_position;
    float d = length(lightVec);
    float a = 3.0f;
    float b = 0.7f;
    float inten = 1.0f / (a * d * d + b *d + 1.0f);

    float ambient = 0.1f;//0.0005f;
    
    // diffuse lighting
    vec3 normal = normalize(normalMap);
    vec3 lightDirection = normalize(lightPos - v_position);
    float diffuse = max(dot(normalMap, lightDirection), 0.0f);

    // specular
    float specular = 0.0f;
    if (diffuse != 0.0f) {
        float specularLight = 0.5f;
        vec3 viewDirection = normalize(v_cameraPos - v_position);
        vec3 reflectionDirection = reflect(-lightDirection, normal);
        float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
        specular = specAmount * specularLight;
    }
    

    return (diffuse + ambient + specular + inten);
}

vec3 checker(in float u, in float v)
{
  float checkSize = 8;
  float fmodResult = mod(floor(checkSize * u) + floor(checkSize * v), 2.0);
  float fin = max(sign(fmodResult), 0.0);
  return vec3(fin, fin, fin);
}

void main()
{
    color = vec4(checker(v_texCoord.x + u_time, v_texCoord.y), 1.0) * vec4(1.0f) * pointLight();
}