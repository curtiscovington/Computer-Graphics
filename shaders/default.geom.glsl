#version 410 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec3 v_position;
out vec4 v_color;
out vec2 v_texCoord;
out vec3 v_normal;
out vec3 v_cameraPos;
out vec3 v_lightPos;

uniform mat4 u_viewProjection;
uniform mat4 u_modelMatrix;
uniform vec3 u_cameraPos;
uniform vec3 u_lightPos;

in DATA
{
    vec2 texCoord;
    vec3 normal;
} data_in[];

void main()
{

    vec3 edge0 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec3 edge1 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec2 deltaUV0 = data_in[1].texCoord - data_in[0].texCoord;
    vec2 deltaUV1 = data_in[2].texCoord - data_in[0].texCoord;

    float invDet = 1.0f / (deltaUV0.x * deltaUV1.y - deltaUV1.x * deltaUV0.y);
    vec3 tangent = vec3(invDet * (deltaUV1.y * edge0 - deltaUV0.y * edge1));
    vec3 bitangent = vec3(invDet * (-deltaUV1.x * edge0 + deltaUV0.x * edge1));

    vec3 T = normalize(vec3(u_modelMatrix * vec4(tangent, 0.0f)));
    vec3 B = normalize(vec3(u_modelMatrix * vec4(bitangent, 0.0f)));
    vec3 N = normalize(vec3(u_modelMatrix * vec4(cross(edge1, edge0), 0.0f)));

    mat3 TBN = mat3(T, B, N);
    TBN = -1 * transpose(TBN);

    for (int i = 0; i < 3; i++)
    {
        gl_Position = u_viewProjection * gl_in[i].gl_Position;
        
        v_texCoord = data_in[i].texCoord;
        v_position = TBN * vec3(gl_in[i].gl_Position);
        v_cameraPos = TBN *  u_cameraPos;
        v_lightPos = TBN * u_lightPos;
        EmitVertex();
    }

    EndPrimitive();
}