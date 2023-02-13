#version 410 core
layout(location = 0) out vec4 color;

uniform sampler2D u_gSampler;
uniform sampler2D u_gSamplerNormalMap;
uniform mat4 u_modelMatrix;

uniform float u_time;

float PHI = 1.61803398874989484820459;  // Φ = Golden Ratio   

float gold_noise(in vec2 xy, in float seed){
       return fract(tan(distance(xy*PHI, xy)*seed)*xy.x);
}

void main()
{
    for(int i=0;i<int(1000000);++i)
    {
        float r = gold_noise(gl_FragCoord.xy, u_time);
        float g = gold_noise(gl_FragCoord.xy, u_time + 1.0);
        float b = gold_noise(gl_FragCoord.xy, u_time + 2.0);
        
        r = step(0.5, r);
        g = step(0.5, g);
        b = step(0.5, b);

        // if (r > 0.5 && g > 0.5 && b > 0.5)
            color = vec4(r, g, b, 0.0);
    }
}
