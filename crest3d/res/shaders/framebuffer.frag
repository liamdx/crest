
#version 330 core
out vec4 FragColor;
  
in vec2 vTexCoords;

uniform sampler2D screenTexture;
uniform sampler2D volumetrics;
uniform float exposure;
uniform float gamma;


vec2 cubic_distortion()
{
    float k = 0;
    float kcube = k * k * k;

    float r2 = (vTexCoords.x - 0.5) * (vTexCoords.x - 0.5) + (vTexCoords.y - 0.5) * (vTexCoords.y - 0.5);
    float f = 0;
    if(kcube == 0.0)
    {
        f = 1 + r2 * k;
    }
    else
    {
        f = 1 + r2 * (k + kcube * sqrt(2));
    }

    vec2 pos;
    pos.x = f * (vTexCoords.x - 0.5) + 0.5;
    pos.y = f * (vTexCoords.y - 0.5) + 0.5;
    return pos;
}

void main()
{
    vec2 pos = cubic_distortion();
    vec4 baseMap = texture2D(screenTexture, pos);
    // reinhard tone mapping
    vec3 mapped = vec3(1.0) - exp(-baseMap.xyz * exposure);
    // Gamma correction 
    mapped = pow(mapped, vec3(1.0 / gamma));
  
    FragColor = vec4(mapped, 1.0);
} 

