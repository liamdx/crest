
#version 330 core
out vec4 FragColor;
  
in vec2 vTexCoords;

uniform sampler2D screenTexture;
uniform float exposure;
uniform float gamma;

const float offset = 1.0 / 300.0;  

void main()
{

    vec4 tex = texture(screenTexture, vTexCoords);
    vec3 col = vec3(tex);

    // reinhard tone mapping
    vec3 mapped = vec3(1.0) - exp(-col * exposure);
    // Gamma correction 
    mapped = pow(mapped, vec3(1.0 / gamma));
  
    FragColor = vec4(mapped, 1.0);
} 