
#version 330 core
out vec4 FragColor;
  
in vec2 vTexCoords;

uniform sampler2D screenTexture;
uniform sampler2D volumetrics;
uniform float exposure;
uniform float gamma;



void main()
{
    vec4 baseMap = texture2D(screenTexture, vTexCoords);

    // reinhard tone mapping
    vec3 mapped = vec3(1.0) - exp(-baseMap.xyz * exposure);
    // Gamma correction 
    mapped = pow(mapped, vec3(1.0 / gamma));
  
    FragColor = vec4(mapped, 1.0);
} 