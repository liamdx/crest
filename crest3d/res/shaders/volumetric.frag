#version 330 core
out vec4 FragColor;
  
in vec2 vTexCoords;

uniform sampler2D screenTexture;
uniform mat4 viewMatrix;
uniform vec3 lightDir;
const float Decay = 0.03;
const float Density = 1.0;
const float offset = 1.0 / 300.0;
const float Exposure = 1.0;
const float Weight = 1.1;

// blur
const float sampleDist = 1.0;
const float sampleStrength = 2.2; 

vec4 volumetric() 
{
    vec2 texCoord = vTexCoords;
    int NUM_SAMPLES = 16;
    vec3 fakeLightPos = vec3(0.0) + ((lightDir) * 20000);
    vec3 ScreenLightPos = vec4(vec4(fakeLightPos, 1.0) * viewMatrix).xyz;

    // Calculate vector from pixel to light source in screen space.
    vec2 deltaTexCoord = (texCoord - ScreenLightPos.xy);
    // Divide by number of samples and scale by control factor.
    deltaTexCoord *= 1.0 / NUM_SAMPLES * Density;
    // Store initial sample.
    vec3 color = texture(screenTexture, texCoord).xyz;
    // Set up illumination decay factor.
    float illuminationDecay = 1.0;
    // Evaluate summation from Equation 3 NUM_SAMPLES iterations.
    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        // Step sample location along ray.
        texCoord -= deltaTexCoord;
        // Retrieve sample at new location.
        vec3 sample = texture(screenTexture, texCoord).xyz;
        // Apply sample attenuation scale/decay factors.
        sample *= illuminationDecay * ((NUM_SAMPLES / i) / NUM_SAMPLES) * Weight;
        // Accumulate combined color.
        color += sample;
        // Update exponential decay factor.
        illuminationDecay *= Decay;
    }
    // Output final color with a further scale control factor.
    return vec4(color * Exposure, 1);
}

void main()
{
    vec4 baseMap = volumetric();
    FragColor = baseMap;
} 